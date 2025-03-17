#include "real_estate_service.h"
#include "real_estate.pb.h"
#include "real_estate.grpc.pb.h"
#include <iostream>
#include <pqxx/pqxx>  // ✅ Only include pqxx here

RealEstateServiceImpl::RealEstateServiceImpl() 
    : db_conn(std::make_unique<ConnectionWrapper>()) {}

grpc::Status RealEstateServiceImpl::StreamPropertyListings(
    grpc::ServerContext* context,
    const realestate::Empty* request,
    grpc::ServerWriter<realestate::Property>* writer) {

    try {
        pqxx::work txn(db_conn->db_conn);
        pqxx::result result = txn.exec(
            "SELECT id, brokered_by, status, price, bed, bath, acre_lot, street, city, state, zip_code, house_size, prev_sold_date FROM properties"
        );

        for (const auto& row : result) {
            realestate::Property property;
            property.set_id(row["id"].is_null() ? 0 : row["id"].as<int>());
            property.set_brokered_by(row["brokered_by"].is_null() ? "N/A" : row["brokered_by"].c_str());
            property.set_status(row["status"].is_null() ? "unknown" : row["status"].c_str());
            property.set_price(row["price"].is_null() ? 0.0 : row["price"].as<double>());
            property.set_bedrooms(row["bed"].is_null() ? 0 : row["bed"].as<int>());
            property.set_bathrooms(row["bath"].is_null() ? 0 : row["bath"].as<int>());
            property.set_acre_lot(row["acre_lot"].is_null() ? 0.0 : row["acre_lot"].as<double>());
            property.set_street(row["street"].is_null() ? "unknown" : row["street"].c_str());
            property.set_city(row["city"].is_null() ? "unknown" : row["city"].c_str());
            property.set_state(row["state"].is_null() ? "unknown" : row["state"].c_str());
            property.set_zip_code(row["zip_code"].is_null() ? "00000" : row["zip_code"].c_str());
            property.set_house_size(row["house_size"].is_null() ? 0.0 : row["house_size"].as<double>());

            property.set_prev_sold_date(row["prev_sold_date"].is_null() ? "N/A" : row["prev_sold_date"].c_str());

            writer->Write(property);
        }

        txn.commit();
        return grpc::Status::OK;
    } catch (const std::exception& e) {
        std::cerr << "Database error in StreamPropertyListings: " << e.what() << std::endl;
        return grpc::Status(grpc::StatusCode::INTERNAL, std::string("Database query failed: ") + e.what());
    }
}

grpc::Status RealEstateServiceImpl::StreamPropertyUpdates(
    grpc::ServerContext* context,
    const realestate::Empty* request,
    grpc::ServerWriter<realestate::PropertyUpdate>* writer) {

    try {
         
        pqxx::work txn(db_conn->db_conn);
        auto result = txn.exec("SELECT id, price, status FROM properties");

        for (const auto& row : result) {
            realestate::PropertyUpdate update;
            update.set_id(row["id"].is_null() ? 0 : row["id"].as<int>());
            update.set_price(row["price"].is_null() ? 0.0 : row["price"].as<double>());
            update.set_status(row["status"].is_null() ? "unknown" : row["status"].c_str());
            
            writer->Write(update);

            
        }

        txn.commit();

        
        

        return grpc::Status::OK;
    } catch (const std::exception& e) {
        std::cerr << "Database error in StreamPropertyUpdates: " << e.what() << std::endl;
        return grpc::Status(grpc::StatusCode::INTERNAL, "Database query failed");
    }
}
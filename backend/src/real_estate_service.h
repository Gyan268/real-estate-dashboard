#ifndef REAL_ESTATE_SERVICE_H
#define REAL_ESTATE_SERVICE_H

#include "real_estate.pb.h"
#include "real_estate.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <memory>

// Include pqxx headers
#include <pqxx/pqxx>  // This ensures that pqxx is properly recognized

class RealEstateServiceImpl final : public realestate::RealEstateService::Service {
private:
    class ConnectionWrapper {
    public:
        pqxx::connection db_conn;

        ConnectionWrapper()
            : db_conn("dbname=real_estate_db user=postgres password=Sairam26800- host=localhost port=5432") {}
    };

    std::unique_ptr<ConnectionWrapper> db_conn;

public:
    RealEstateServiceImpl();
    grpc::Status StreamPropertyListings(
        grpc::ServerContext* context,
        const realestate::Empty* request,
        grpc::ServerWriter<realestate::Property>* writer) override;
    
    grpc::Status StreamPropertyUpdates(
        grpc::ServerContext* context,
        const realestate::Empty* request,
        grpc::ServerWriter<realestate::PropertyUpdate>* writer) override;
};

#endif
#include <grpcpp/grpcpp.h>
#include "real_estate_service.h"
#include <iostream>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    RealEstateServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main() {
    RunServer();
    return 0;
}
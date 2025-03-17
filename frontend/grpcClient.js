const { RealEstateServiceClient } = require("./proto/real_estate_grpc_web_pb.js");
const { Empty } = require("./proto/real_estate_pb.js");

// Initialize the gRPC client with the backend URL
const client = new RealEstateServiceClient("http://localhost:8080");

module.exports = { client, Empty };
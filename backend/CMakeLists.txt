cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(RealEstateDashboard)

# Set paths for Protobuf and gRPC
set(Protobuf_DIR "/opt/homebrew/lib/cmake/protobuf")
set(gRPC_DIR "/opt/homebrew/lib/cmake/grpc")
set(absl_DIR "/opt/homebrew/lib/cmake/absl")

# Find required packages
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)

# Find PostgreSQL and libpqxx
find_library(PQXX_LIB pqxx PATHS /opt/homebrew/lib /usr/local/lib /usr/lib /opt/homebrew/opt/libpqxx/lib)
find_library(PQ_LIB pq PATHS /opt/homebrew/lib /usr/local/lib /usr/lib /opt/homebrew/opt/libpq/lib)

# Define source files
file(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.pb.cc" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.grpc.pb.cc")

add_executable(real_estate_server 
    src/main.cpp 
    src/real_estate_service.cpp 
    ${PROTO_FILES})

# Include directories
target_include_directories(real_estate_server PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src 
    ${Protobuf_INCLUDE_DIRS}
    /opt/homebrew/include
    /opt/homebrew/include/grpc
    /usr/local/include
    /usr/include
)

# Link libraries 
target_link_libraries(real_estate_server
    gRPC::grpc++
    protobuf::libprotobuf
    gRPC::grpc++_reflection  
    ${PQXX_LIB}  
    ${PQ_LIB}    
    absl::strings
    absl::status
    absl::flat_hash_map
    absl::check
    absl::any_invocable
    absl::no_destructor
)
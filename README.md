# Real-Time Real Estate Market Dashboard

## Overview
The **Real-Time Real Estate Market Dashboard** is a full-stack application that streams live real estate data to connected clients. It showcases expertise in **asynchronous data processing, server streaming, frontend visualization, and database management** using cutting-edge technologies.

## Features
- **Real-Time Data Streaming**: Uses **gRPC server-streaming** to push live real estate updates to connected clients.
- **Full-Stack Development**:
  - **Backend (C++)**: Handles data processing, gRPC streaming, and API logic.
  - **Frontend (JavaScript, HTML, CSS)**: Displays real-time property listings in an interactive UI.
- **Database Integration**: Stores and manages real estate listings using **PostgreSQL**.
- **Asynchronous Processing**: Implements efficient data fetching from an external API or simulated data source.
- **Scalable Architecture**: Designed to handle high-frequency updates efficiently.

## Tech Stack
### **Backend (C++ with gRPC)**
- C++
- gRPC (for server streaming)
- PostgreSQL (database)
- RESTful API support
- Multithreading for handling concurrent client connections

### **Frontend (JavaScript, HTML, CSS)**
- JavaScript (Vanilla or with a framework if needed)
- HTML5 & CSS3 for UI design
- Real-time data updates using gRPC client

### **Database**
- PostgreSQL for structured data storage

### **Development & Deployment**
- **Git & GitHub** for version control
- **Docker (Future Enhancement)** for containerized deployment
- **CI/CD Pipelines (Future Enhancement)** for automated deployments

## Installation & Setup
### **Backend Setup**
1. Clone the repository:
   ```bash
   git clone https://github.com/Gyan268/real-estate-dashboard.git
   cd real-estate-dashboard/backend

2. Install necessary dependencies (adjust based on C++ environment):
   ```bash
   sudo apt-get install -y grpc-dev protobuf-compiler

3. Compile and run the gRPC server:
   ```bash
   g++ -o server server.cpp -lgrpc++ -lprotobuf
   ./server

### **Frontend Setup**
1. Navigate to the frontend directory:
   ```bash
   cd ../frontend

2. Start a simple HTTP server (if using vanilla JavaScript):
   ```bash
   python3 -m http.server 8080

3. Open http://localhost:8080 in a browser.

## Usage
- Once the backend server is running, the frontend will automatically receive real-time property updates.
- The gRPC client in JavaScript subscribes to property updates and dynamically updates the UI.

## Future Enhancements
- Deploy using Docker & Kubernetes
- Implement Authentication & User Accounts
- Integrate with a Real Estate API for live data
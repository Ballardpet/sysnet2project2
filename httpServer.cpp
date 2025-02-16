#include "httpServer.hpp"

#include <iostream> 
#include <fstream>        //Standard libray for file input and output
#include <sstream>        //Standard library for working with string streams
#include <string> 
#include <sys/socket.h>   //API and definitions for the sockets
#include <netinet/in.h>   //Structures to store address information
#include <unistd.h>       //Standard library for system calls
#include <thread>         //Standard library for creating and managing threads
#include <csignal>        //Standard library for handling signals

httpServer::httpServer(const std::string& port) : port(port), server_socket_fd(-1) {}  

//creates and configures the server socket
bool httpServer::start() {
        struct sockaddr_in server_addr{}; //structure to store server address (used for configuring and binding the socket)

        //Create a socket for the server
        server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket_fd < 0) {
            std::cerr << "Failed to create server socket." << std::endl;
            return false;
        }
//Config server socket, INADDR allows the server to listen on all available network interfaces
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(std::stoi(port));
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

//Bind socket to port
        if (bind(server_socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Failed to bind server socket." << std::endl;
            close(server_socket_fd);
            return false;
        }
//Listens on socket
        if (listen(server_socket_fd, 5) < 0) {
            std::cerr << "Failed to listen on server socket." << std::endl;
            close(server_socket_fd);
            return false;
        }

        std::cout << "Server started on port: " << port << std::endl;

        return true;
}

//Loop to conect to client socket
void httpServer::run() {
    while (true) {
        int client_socket_fd = accept(server_socket_fd, nullptr, nullptr);
        if (client_socket_fd < 0) {
            std::cerr << "Failed to accept connection." << std::endl;
            continue;
        }
        std::thread(&httpServer::handleClient, this, client_socket_fd).detach();
        }
}
//Handles the client request
void httpServer::handleClient(int client_socket_fd) {

    
    char buffer[1024]; //Buffer to store incoming request data from the client
    read(client_socket_fd, buffer, sizeof(buffer)); //Read data from the client socket

    std::cout << buffer;

    std::istringstream request(buffer); //Parsing the incoming request using stringstream
    std::string method, path, version;
    request >> method >> path >> version; //Extracts the HTTP method, path and version from the request

//Checks if the method is GET and version is HTTP/1.1, if not, it displays notice and close the connection
    if (method != "GET" || version != "HTTP/1.1") {
        send_response(client_socket_fd, "400 Bad Request", "Invalid HTTP request.");
        close(client_socket_fd);
        return;
    }

    path = path.substr(1); //remove leading '/'
    if (path.empty()) path = "index.html"; //reading the given file

    std::ifstream file(path); //Opens the requested file
    if (!file.is_open()) {
        send_response(client_socket_fd, "404 Not Found", "The requested file was not found."); //responds if file not found
    } else {
        std::ostringstream file_content;
        file_content << file.rdbuf(); //Read the files's content into stringstream
        send_response(client_socket_fd, "200 OK", file_content.str(), "text/html");
    }
//close the client socket
    close(client_socket_fd);
}
//Sends an HTTP response to the client
void httpServer::send_response(int client_socket_fd, const std::string& status, const std::string& content, const std::string& content_type) {
    std::ostringstream response;
    //Build the HTTP response with status, headers and content
    response << "HTTP/1.1 " << status << "\r\n"
                << "Content-Type: " << content_type << "\r\n"
                << "Content-Length: " << content.size() << "\r\n"
                << "\r\n"
                << content;

    //Sent the response to the client socket            
    send(client_socket_fd, response.str().c_str(), response.str().size(), 0); 
}
void httpServer::sendErrorResponse(int clientSocket, const std::string& status, const std::string& message) {
    std::ostringstream oss;
    oss << "<html><body><h1>" << status << "</h1><p>" << message << "</p></body></html>";

    std::string content = oss.str();
    send_response(clientSocket, status, "text/html", content);
}

//Destructor
httpServer::~httpServer() {
    if (server_socket_fd >= 0) close(server_socket_fd);
    close(server_socket_fd); //Close the server socket
}
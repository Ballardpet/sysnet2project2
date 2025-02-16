#include "httpClient.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <fstream>

#define BUFFER_SIZE 4096

void fetchFile(const std::string& server_ip, int port, const std::string& filename) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        std::cerr << "Error: Could not create socket." << std::endl;
        return;
    }
    
    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid server IP address." << std::endl;
        close(client_socket);
        return;
    }
    
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: Could not connect to server." << std::endl;
        close(client_socket);
        return;
    }
    
// Forming the HTTP GET request
std::ostringstream request;
request << "GET /" << filename << " HTTP/1.1\r\n";
request << "Host: " << server_ip << "\r\n";
request << "Connection: close\r\n\r\n";

std::string request_str = request.str();
send(client_socket, request_str.c_str(), request_str.size(), 0);

char buffer[BUFFER_SIZE];




// Sets a standard name for an output file to prevent override when downloading existing files
std::string outputFileName = "OutputFile" + filename.substr(filename.length() - 4, 4);

// Open a file to save the response body
std::ofstream output_file(outputFileName, std::ios::binary); //// 
    if (!output_file) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        close(client_socket);
        return;
    }

    //char buffer[BUFFER_SIZE];
    bool header_parsed = false;
    std::string response;


    bool check = true;

    while (true) {
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (check){
            printf("\n\nServer says: %s \n", buffer);
            check = false;
        }
        if (bytes_received <= 0) break;
    
            if (!header_parsed) {
                response.append(buffer, bytes_received);
                size_t header_end = response.find("\r\n\r\n");
            if (header_end != std::string::npos) {
            // Skip headers and write only the body
                output_file.write(response.c_str() + header_end + 4, response.size() - header_end - 4);
                header_parsed = true;
            }
            } else {
            output_file.write(buffer, bytes_received);
            }
    }

    std::cout << "File '" << filename << "' downloaded successfully." << std::endl; /////
    output_file.close();
    
    close(client_socket);
}
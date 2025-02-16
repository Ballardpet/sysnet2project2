#include "httpClient.hpp"
#include <iostream>

int main() {
    std::string server_ip, filename;
    int port;
    
    std::cout << "Enter server IP: ";
    std::cin >> server_ip;
    std::cout << "Enter server port: ";
    std::cin >> port;
    
    while (true) {
        std::cout << "Enter filename to fetch (or type 'exit' to quit): ";
        std::cin >> filename;
        
        if (filename == "exit") break;
        fetchFile(server_ip, port, filename);
    }
    
    std::cout << "Client exiting..." << std::endl;
    return 0;
}

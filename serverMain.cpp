#include "httpServer.hpp"
#include <iostream>
#include <string>

int main() {
    std::string port = "60069";; // Valid port number range: 60001 – 60099
    httpServer httpServer(port);
    
    if(!httpServer.start()){
        return 1;
    }
    httpServer.run();
    return 0;
}
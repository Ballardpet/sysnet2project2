#include "httpServer.hpp"

int main(){
    std::string port = "60069";
    httpServer httpServer(port);
    
    if(!httpServer.start()){
        return 1;
    }
    httpServer.run();
    return 0;
    
}
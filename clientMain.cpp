#include "httpClient.hpp"

int main(){
    std::string port = "60069";
    httpClient httpClient(port);

    if(!httpClient.start()){
        return 1;
    }
    httpClient.run();
    return 0;
}
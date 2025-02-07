#include "httpClient.hpp"

httpClient::httpClient(const std::string& port) : port(port){}

bool httpClient::start(){
    
    // creating the TCP socket
    tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0); //Calling the socketfunction - args: socket domain, socket stream type, TCP protocol (default)
    if (tcp_client_socket < 0) {
        std::cerr << "Failed to create client socket." << std::endl;
        return false;
    }

    tcp_server_address.sin_family = AF_INET; //Structure Fields' definition: Sets the address family of the address the client would connect to
    tcp_server_address.sin_port = htons(std::stoi(port)); //Specify and pass the port number to connect - converting in right network byte order
    tcp_server_address.sin_addr.s_addr = INADDR_ANY; //Connecting to 0.0.0.0


    // connecting to the remote socket
    int connection_status = connect(tcp_client_socket, (struct sockaddr *) &tcp_server_address, sizeof(tcp_server_address)); //params: which socket, cast for address to the specific structure type, size of address
    if (connection_status == -1){   //return value of 0 means all okay, -1 means a problem
        std::cerr << "Problem connecting to the socket. \n" << std::endl;
        return false;
    }

    std::cerr << "Connected to the socket! \n" << std::endl;
    return true;
}

void httpClient::run(){

    while(true){
        char tcp_server_response[256];
        recv(tcp_client_socket, &tcp_server_response, sizeof(tcp_server_response), 0);
        printf("\n\n Server says: %s \n", tcp_server_response);
    }

    close(tcp_client_socket);
}

//Destructor
httpClient::~httpClient() {
    if (tcp_client_socket >= 0) close(tcp_client_socket);
    close(tcp_client_socket); //Close the server socket
}
#include "httpClient.hpp"

#include <stdio.h> //Standard library
#include <stdlib.h> //Standard library
#include <sys/socket.h> //API and definitions for the sockets
#include <sys/types.h> //more definitions
#include <netinet/in.h> //Structures to store address information
#include <unistd.h> //Standard library for system calls
#include <iostream>

httpClient::httpClient(/*some shit here*/){} // HERE HERE

bool httpClient::start(){
    struct sockaddr_in tcp_server_address; //declaring a structure for the address
    
    tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0); //Calling the socketfunction - args: socket domain, socket stream type, TCP protocol (default)
    if (tcp_client_socket < 0) {
        std::cerr << "Failed to create client socket." << std::endl;
        printf("Failed to create client socket. \n");
        return false;
    }

    tcp_server_address.sin_family = AF_INET; //Structure Fields' definition: Sets the address family of the address the client would connect to
    tcp_server_address.sin_port = htons(39756); //Specify and pass the port number to connect - converting in right network byte order
    tcp_server_address.sin_addr.s_addr = INADDR_ANY; //Connecting to 0.0.0.0

    // DELETE THIS. Don't think it binds to port. Don't think it needs to listen

    // Make a cout to say "client started" or some shit. HERE HERE


    // This here seems to be where it actually connects to the server. MAYBE set to another function?
        // everything forward should maybe be in another function that loops. Research this and look at other file
    int connection_status = connect(tcp_client_socket, (struct sockaddr *) &tcp_server_address, sizeof(tcp_server_address)); //params: which socket, cast for address to the specific structure type, size of address if (connection_status == -1){
    if (connection_status == -1){   //return value of 0 means all okay, -1 means a problem
        std::cerr << "Problem connecting to the socket! Sorry!! \n" << std::endl;
        printf(" Problem connecting to the socket! Sorry!! \n");
        return false;
    }
}

void httpClient::run(){
    // GET USER INPUT FOR SERVER SHIT HERE HERE

    // IP address should be set. HERE HERE
    // Port should be received as input from user HERE HERE

    int tcp_server_socket = 5; // PUT THE ACTUAL REAL SHIT HERE !!!!.
    if (tcp_server_socket < 0) {
        std::cerr << "Failed to accept connection." << std::endl;
        printf("Failed to connect.");
    }
    // no while true here. Doesn't connect to multiple servers here
    else{
        handle_server(tcp_server_socket);
    }
}

void httpClient::handle_server(int tcp_server_socket){
    // while(true) here?

    // CONNECT TO SERVER HERE I THINK HERE HERE

    while (true){
        char tcp_server_response[256];
        recv(tcp_client_socket, &tcp_server_response, sizeof(tcp_server_response), 0);

        // HANDLE ERRORS HERE !!!!! HERE HERE

        //Output, as received from Server
        printf("\n\n Server says: %s \n", tcp_server_response);

        // MAKE A CONDITION TO CLOSE THIS !!! HERE HERE
    }

    close(tcp_client_socket);
}

//Destructor
httpClient::~httpClient() {
    if (tcp_client_socket >= 0) close(tcp_client_socket);
    close(tcp_client_socket); //Close the server socket
}
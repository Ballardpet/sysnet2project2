// request user to enter the name of the http server followed by
// the name of a file on that server

// client should send a vaild HTTP/1.1 request ro the server for the file

// client program should display all the responses received from the server
    // Make sure the client program guides the user about the right usage
    // before promting the user and waiting on a client request

    // also make sure the user can request for more files in the same way 
    // rather than exiting immediately

    // If server is still active and listening, it should respond accordingly

    // If server has stopped working, it should also be indicated in the running
    // client program

    // Be verbose !!!

#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <string>
#include <stdio.h> //Standard library
#include <stdlib.h> //Standard library
#include <sys/socket.h> //API and definitions for the sockets
#include <sys/types.h> //more definitions
#include <netinet/in.h> //Structures to store address information
#include <unistd.h> //Standard library for system calls
#include <iostream>

class httpClient{
    private:
        std::string port;
        struct sockaddr_in tcp_server_address; //declaring a structure for the address
        int tcp_client_socket;
        void send_request(int tcp_server_socket, const std::string& status, const std::string& content, const std::string& content_type = "text/plain"); // not 100% sure if this is right
    public:
        httpClient(const std::string& port);
        bool start(); // ?
        void run(); //?
        ~httpClient();
};


#endif
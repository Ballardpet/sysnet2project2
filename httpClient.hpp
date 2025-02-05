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

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include <string>

class httpClient{
    private:
        int tcp_client_socket;
        void handle_server(int tcp_server_socket); //gott check this too
        void send_request(int tcp_server_socket, const std::string& status, const std::string& content, const std::string& content_type = "text/plain"); // not 100% sure if this is right
    public:
        httpClient(/*Some shit here maybe*/);
        bool start(); // ?
        void run(); //?
        ~httpClient();
};


#endif
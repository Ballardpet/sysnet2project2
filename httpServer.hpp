/*********************************************/
/* Program Name: Project1                    */
/* Authors: Nan Stephanishen & Peter Ballard */
/* Date: 2025-01-26                          */
/* Description: Header file for httpServer   */
/*********************************************/
#ifndef HTTPSERVER_HPP  //PB
#define HTTPSERVER_HPP  //PB

#include <string>

//Creating httpServer class
class httpServer {
    private:
        std::string port;
        int server_socket_fd;
        void handle_client(int client_socket_fd);
        void send_response(int client_socket_fd, const std::string& status, const std::string& content, const std::string& content_type = "text/plain");
    public:
        httpServer(const std::string& port);
        bool start();
        void run();
        ~httpServer();
};

#endif
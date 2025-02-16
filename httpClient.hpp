#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <string>

void fetchFile(const std::string& server_ip, int port, const std::string& filename);

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
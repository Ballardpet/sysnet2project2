#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include <string>
#include <unordered_map>

class httpServer {
public:
    httpServer(const std::string& port);
    bool start();
    void run();
    ~httpServer();
private:
    std::string port;
    std::unordered_map<std::string, std::string> fileMap;
    int server_socket_fd;
    void handleClient(int client_socket_fd);
    std::string getMimeType(const std::string& filePath);
    void send_response(int client_socket_fd, const std::string& status, const std::string& content, const std::string& content_type = "text/plain");
    void sendErrorResponse(int clientSocket, const std::string& status, const std::string& message);
};

#endif // HTTPSERVER_HPP
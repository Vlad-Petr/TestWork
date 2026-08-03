#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <string> 

class SocketServer {
private:
    int server_fd;   
    int client_fd;
    int port;
    bool is_connected;

public:
    explicit SocketServer(int port);
    
    ~SocketServer();

    bool waitForConnection();

    //bool sendData(const std::string& data);
    bool sendData(const std::string& input_string, long long sum);

    void disconnectClient();
};

#endif
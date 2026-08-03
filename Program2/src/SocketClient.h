#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <string>

class SocketClient {
private:
    int client_fd;
    std::string server_ip;
    int port;
    bool is_connected;

public:
    SocketClient(const std::string& ip, int port);
    ~SocketClient();
    
    bool connectToServer();
    bool receiveData(std::string& out_string, long long& out_sum);
    void disconnect();
};

#endif
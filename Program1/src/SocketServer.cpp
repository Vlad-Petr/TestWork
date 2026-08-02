#include "SocketServer.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>      // Для close()
#include <arpa/inet.h>   // Для inet_ntoa
#include <cstring>       // Для memset

SocketServer::SocketServer(int port) : 
server_fd(-1), client_fd(-1), port(port), is_connected(false) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Ошибка привязки bind к порту " << port << std::endl;
        close(server_fd);
        server_fd = -1;
        return;
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Ошибка перевода сокета в режим прослушивания listen" << std::endl;
        close(server_fd);
        server_fd = -1;
        return;
    }

    std::cout << "[Сеть] Сервер запущен и ожидает подключений на порту " << port << "..." << std::endl;
}

SocketServer::~SocketServer() {
    disconnectClient();
    if (server_fd >= 0) {
        close(server_fd);
    }
}

bool SocketServer::waitForConnection() {
    if (server_fd < 0) return false;
    if (is_connected) return true;

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    std::cout << "[Сеть] Ожидание подключения Программы 2..." << std::endl;
    
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    
    if (client_fd < 0) {
        std::cerr << "Ошибка приёма соединения accept" << std::endl;
        return false;
    }

    is_connected = true;
    std::cout << "[Сеть] Программа 2 успешно подключилась!" << std::endl;
    return true;
}

bool SocketServer::sendData(const std::string& data) {
    if (!is_connected || client_fd < 0) {
        if (!waitForConnection()) {
            return false;
        }
    }

    std::string payload = data + "\n";
    
    ssize_t bytes_sent = send(client_fd, payload.c_str(), payload.length(), 0);
    
    if (bytes_sent <= 0) {
        std::cout << "[Сеть] Программа 2 отключилась." << std::endl;
        disconnectClient();
        return false;
    }
    
    return true;
}

void SocketServer::disconnectClient() {
    if (client_fd >= 0) {
        close(client_fd);
        client_fd = -1;
    }
    is_connected = false;
}
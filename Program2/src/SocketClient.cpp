#include "SocketClient.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

SocketClient::SocketClient(const string& ip, int port) 
    : client_fd(-1), server_ip(ip), port(port), is_connected(false) {}

SocketClient::~SocketClient() { disconnect(); }

bool SocketClient::connectToServer() {
    if (is_connected) {
        return true;
    }

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        cerr << "[Сеть] Ошибка создания сокета!" << endl;
        return false;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        cerr << "[Сеть] Неверный IP адрес: " << server_ip << endl;
        close(client_fd);
        client_fd = -1;
        return false;
    }

    cout << "[Сеть] Подключение к Программе 1 на " << server_ip << ":" << port << "..." << endl;
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "[Сеть] Не удалось подключиться к Программе 1" << endl;
        close(client_fd);
        client_fd = -1;
        return false;
    }

    is_connected = true;
    cout << "[Сеть] Успешно подключено к Программе 1!" << endl;
    return true;
}

bool SocketClient::receiveData(string& out_string, long long& out_sum) {
    if (!is_connected) {
        if (!connectToServer()) {
            return false;
        }
    }

    char buffer[1024] = {0};
    
    ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes_read <= 0) {
        if (bytes_read == 0) {
            cout << "[Сеть] Программа 1 закрыла соединение" << endl;
        } else {
            cerr << "[Сеть] Ошибка приёма данных" << endl;
        }
        disconnect();
        return false;
    }

    buffer[bytes_read] = '\0';
    string received(buffer);
    
    if (!received.empty() && received.back() == '\n') {
        received.pop_back();
    }

    size_t delimiter_pos = received.rfind('|');
    if (delimiter_pos == string::npos) {
        cerr << "[Сеть] Ошибка парсинга: не найден разделитель '|'" << endl;
        return false;
    }

    out_string = received.substr(0, delimiter_pos);
    
    try {
        out_sum = stoll(received.substr(delimiter_pos + 1));
    } catch (const exception& e) {
        cerr << "[Сеть] Ошибка преобразования суммы: " << e.what() << endl;
        return false;
    }

    return true;
}

void SocketClient::disconnect() {
    if (client_fd >= 0) {
        close(client_fd);
        client_fd = -1;
    }
    is_connected = false;
}
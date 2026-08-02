#include "Consumer.h"
#include <iostream>

using namespace std;

extern "C" long long sumNumbers(const char* inputString);

Consumer::Consumer(Buffer& buf) : buffer(buf), running(false), network(8080) {}

Consumer::~Consumer() { stop(); }

void Consumer::start() {
    if (!running) {
        running = true;
        thread = std::thread(&Consumer::run, this);
    }
}

void Consumer::stop() {
    if (running) {
        running = false;
        buffer.shutdown();
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void Consumer::processData(const string& data) {
    cout << "\n=== Поток 2 получил данные ===" << endl;
    cout << "Данные: " << data << endl;
    
    long long sum = sumNumbers(data.c_str());
    cout << "Сумма чисел: " << sum << endl;
    
    string messageToSend = to_string(sum);
    
    if (network.sendData(messageToSend)) {
        cout << "[Сеть] Результат успешно передан в Программу 2." << endl;
    } else {
        cout << "[Сеть] Не удалось передать данные (ожидание перезапуска Программы 2...)." << endl;
    }
    
    cout << "================================\n" << endl;
}

void Consumer::run() {
    while (running) {
        string data = buffer.getString();
        
        if (data.empty() && !running) {
            break;
        }

        processData(data);
    }
}
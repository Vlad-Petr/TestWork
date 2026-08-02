#ifndef CONSUMER_H
#define CONSUMER_H

#include <thread>
#include <string>
#include "Buffer.h"
#include "SocketServer.h"

class Consumer {
private:
    Buffer& buffer;
    std::thread thread;
    bool running;
    SocketServer network;

    void run();

    void processData(const std::string& data);

public:
    Consumer(Buffer& buf);
    ~Consumer();

    void start();
    void stop();
};

#endif
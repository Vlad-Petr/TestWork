#ifndef PRODUCER_H
#define PRODUCER_H

#include <thread>
#include <string>
#include "Buffer.h"

class Producer {
private:
    Buffer& buffer;
    std::thread thread;
    bool running;

    void run();

    bool validateString(const std::string& input, std::string& errorMsg);

public:
    Producer(Buffer& buf);
    ~Producer();

    void start();
    void stop();
};

#endif 
#ifndef BUFFER_H
#define BUFFER_H

#include <mutex>
#include <condition_variable>
#include <string>

class Buffer {
private:
    std::string data;
    bool hasData;
    bool shutdownFlag;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Buffer() : hasData(false), shutdownFlag(false) {}

    void putString(const std::string& input) {
        std::unique_lock<std::mutex> lock(mtx);
        if (shutdownFlag) return;
        
        data = input;
        hasData = true;
        cv.notify_one(); 
    }

    std::string getString() {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [this] { return hasData || shutdownFlag; });
        
        if (shutdownFlag && !hasData) {
            return ""; 
        }
        
        std::string result = data;
        data.clear();
        hasData = false;
        return result;
    }

    void shutdown() {
        std::unique_lock<std::mutex> lock(mtx);
        shutdownFlag = true;
        cv.notify_all();  
    }
};

#endif
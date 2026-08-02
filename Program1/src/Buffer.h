#ifndef BUFFER_H
#define BUFFER_H

#include <mutex>
#include <condition_variable>
#include <string>

class Buffer {
private:
    string data;
    bool hasData;
    bool shutdownFlag;
    mutex mtx;
    condition_variable cv;

public:
    Buffer() : hasData(false), shutdownFlag(false) {}

    void putString(const string& input) {
        unique_lock<mutex> lock(mtx);
        if (shutdownFlag) return;
        
        data = input;
        hasData = true;
        cv.notify_one();  // Будим поток 2
    }

    string getString() {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [this] { return hasData || shutdownFlag; });
        
        if (shutdownFlag && !hasData) {
            return ""; 
        }
        
        string result = data;
        data.clear();
        hasData = false;
        return result;
    }

    void shutdown() {
        unique_lock<mutex> lock(mtx);
        shutdownFlag = true;
        cv.notify_all();  
    }
};

#endif
#include "Producer.h"
#include <iostream>
#include <string.h> 

using namespace std;

extern "C" void sortAndReplace(char* inputString);

Producer::Producer(Buffer& buf) : buffer(buf), running(false) {}

Producer::~Producer() { stop(); }

void Producer::start() {
    if (!running) {
        running = true;
        thread = std::thread(&Producer::run, this);
    }
}

void Producer::stop() {
    if (running) {
        running = false;
        if (thread.joinable()) {
            thread.join();
        }
    }
}

bool Producer::validateString(const string& input, string& errorMsg) {
    if (input.length() > 64) {
        errorMsg = "Ошибка: строка превышает 64 символа (длина: " + 
                   to_string(input.length()) + ")";
        return false;
    }

    if (input.empty()) {
        errorMsg = "Ошибка: строка пустая";
        return false;
    }

    for (int i = 0; i < input.length(); i++) {
        if (!isdigit(static_cast<unsigned char>(input[i]))) {
            errorMsg = "Ошибка: строка содержит недопустимый символ '" + 
                       string(1, input[i]) + "' на позиции " + 
                       to_string(i + 1);
            return false;
        }
    }

    return true;
}


void Producer::run() {
    while (running) {
        string input;
        cout << "Введите строку (только цифры, 64 символа максимум): ";
        getline(cin, input);

        string errorMsg;
        if (!validateString(input, errorMsg)) {
            cout << errorMsg << endl;
            continue;
        }

        size_t bufferSize = input.length() * 2 + 1;
        char* buffer_copy = new char[bufferSize];
        snprintf(buffer_copy, bufferSize, "%s", input.c_str());

        sortAndReplace(buffer_copy);
        buffer.putString(string(buffer_copy));

        delete[] buffer_copy;
    }
}
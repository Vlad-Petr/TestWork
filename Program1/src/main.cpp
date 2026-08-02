#include <iostream>
#include "Buffer.h"
#include "Producer.h"
#include "Consumer.h"

using namespace std;

int main() {
    cout << "Программа запущена" << endl;

    Buffer buffer;
    Producer producer(buffer);
    Consumer consumer(buffer);

    producer.start();
    consumer.start();

    cout << "Потоки запущены. Введите 'exit' для завершения." << endl;

    string command;
    while (true) {
        getline(cin, command);
        if (command == "exit") {
            break;
        }
    }

    producer.stop();
    consumer.stop();

    cout << "Программа завершена" << endl;
    return 0;
}
#include <iostream>
#include <string>
#include "SocketClient.h"

using namespace std;

extern "C" bool checkString(const char* inputString, long long sum);

int main() {
    cout << "=== Программа 2 запущена ===" << endl;

    SocketClient client("127.0.0.1", 8080);

    while (true) {
        string received_string;
        long long received_sum;

        if (!client.receiveData(received_string, received_sum)) {
            cout << "[Сеть] Потеряно соединение с Программой 1. Ожидаю подключения" << endl;

            continue;
        }

        cout << "\n=== Получены данные от Программы 1 ===" << endl;
        cout << "Строка: " << received_string << endl;
        cout << "Сумма: " << received_sum << endl;

        bool result = checkString(received_string.c_str(), received_sum);

        if (result) {
            cout << "ПРОВЕРКА УСПЕШНА:" << endl;
            cout << "Длина строки > 2" << endl;
            cout << "Сумма (" << received_sum << ") кратна 32" << endl;
        } else {
            cout << "ОШИБКА ПРОВЕРКИ:" << endl;
            if (received_string.length() <= 2) {
                cout << "Длина строки <= 2" << endl;
            }
            if (received_sum == 0) {
                cout << "Сумма равна 0" << endl;
            } else if (received_sum % 32 != 0) {
                cout << "Сумма (" << received_sum << ") не кратна 32" << endl;
            }
        }

        cout << "=====================================\n" << endl;
    }

    return 0;
}
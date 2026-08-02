#include <iostream>
#include "stringsLib.h"

int main() {
    setlocale(LC_ALL, "RU");
    char testStr[129] = "12345566755899";
    std::cout << "Исходная строка: \"" << testStr << "\"" << std::endl;

    sortAndReplace(testStr);
    std::cout << "Cтрока с заменой: \"" << testStr << "\"" << std::endl;

    long long result = sumNumbers(testStr);
    std::cout << "Сумма чисел: " << result << std::endl;

    bool res2 = checkString(testStr, result);
    std::cout << "Проверка: \"" << res2 << "\"" << std::endl;

    return 0;
}
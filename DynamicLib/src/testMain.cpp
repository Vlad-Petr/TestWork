#include <iostream>
#include "stringsLib.h"

int main() {
    const char* testStr = "7KB313KB999";
    
    double result = sumNumbers(testStr);
    
    std::cout << "Исходная строка: \"" << testStr << "\"" << std::endl;
    std::cout << "Сумма чисел: " << result << std::endl;
    
    return 0;
}
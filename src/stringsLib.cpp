#include "stringsLib.h"



double sumNumbers(const char* inputString) {
    double sum = 0.0;
    long long curNumber = 0.0;
    bool isNumber = false;

    const char ZERO_CH = '0', NINE_CH = '9', STR_END_CH = '\0';
    const int TEN = 10;

    for (int i = 0; inputString[i] != STR_END_CH; i++) {
        char c = inputString[i];

        if (c >= ZERO_CH && c <= NINE_CH) {
            curNumber = curNumber * TEN + (c - ZERO_CH);
            isNumber = true;
        } else {
            if (isNumber) {
                sum += curNumber;
                curNumber = 0;
                isNumber = false;
            }
        }
    }
    
    if (isNumber) {
        sum += curNumber;
    }

    return sum;
}
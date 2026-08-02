#include "stringsLib.h"
#include <algorithm>
#include <string.h> 
using namespace std;

const char ZERO_CH = '0', STR_END_CH = '\0';

void sortAndReplace(char* inputString) {

    int len = static_cast<int>(strlen(inputString));
    sort(inputString, inputString + len, [](char a, char b) { return a > b; });

    const int MAX_SIZE = 129;
    char result[MAX_SIZE]{};

    const char K_CH = 'K', B_CH = 'B';

    int pos = 0;
    for (int i = 0; i < len; i++) {
        char c = inputString[i];
        int digit = c - ZERO_CH;
        if (digit % 2 == 0) {
            result[pos++] = K_CH;
            result[pos++] = B_CH;
        }
        else {
            result[pos++] = c;
        }
    }
    result[pos] = STR_END_CH;

    int lenResult = static_cast<int>(strlen(result));
    copy(result, result+lenResult, inputString);
}


long long sumNumbers(const char* inputString) {
    long long sum = 0;
    long long curNumber = 0;
    bool isNumber = false;

    const char NINE_CH = '9';
    const int TEN = 10;

    for (int i = 0; inputString[i] != STR_END_CH; i++) {
        char c = inputString[i];

        if (c >= ZERO_CH && c <= NINE_CH) {
            curNumber = curNumber * TEN + (c - ZERO_CH);
            isNumber = true;
        }
        else {
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

bool checkString(const char* inputString, long long sum) {
    if (sum == 0) { return false; }

    int length = static_cast<int>(strlen(inputString));
    if (length <= 2) { return false; }

    if (sum % 32 == 0) { return true; }

    return false;
}
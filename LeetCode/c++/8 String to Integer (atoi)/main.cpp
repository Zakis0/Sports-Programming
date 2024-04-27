// https://leetcode.com/problems/string-to-integer-atoi/

#include <iostream>

using namespace std;

#define INT_MIN (-2147483647 - 1)
#define INT_MAX (2147483647)

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isWhitespace(char c) {
    return c == ' ';
}

bool isSignCharacter(char c) {
    return c == '-' || c == '+';
}

bool isZero(char c) {
    return c == '0';
}

int myAtoi(string s) {
    int sign = 1, result = 0;
    long long temp;
    bool hasDigit = false, hasSign = false, hasNonZeroDigit = false;
    for (char i : s) {
        if (isDigit(i)) {
            hasDigit = true;
            if (!isZero(i)) {
                hasNonZeroDigit = true;
            }
            if (hasNonZeroDigit) {
                temp = (long long)result * 10 + i - '0';
                if (sign == -1 && (sign * temp) <= INT_MIN) {
                    return INT_MIN;
                }
                else if (sign == 1 && temp >= INT_MAX) {
                    return INT_MAX;
                }
                result = (int)temp;
            }
        }
        else if (!hasDigit && !isWhitespace(i) && !isSignCharacter(i) && !isDigit(i)) {
            return 0;
        }
        else if (hasDigit && !isDigit(i)) {
            return result * sign;
        }
        else if (isWhitespace(i)) {
            if (hasDigit || hasSign) {
                return 0;
            }
            continue;
        }
        else if (isSignCharacter(i)) {
            if (hasSign) {
                return 0;
            }
            if (i == '-') {
                sign = -1;
            }
            hasSign = true;
        }
        else {
            return 0;
        }
    }
    return result * sign;
}

int main() {
    cout << myAtoi("21474836460") << endl;
//    cout << (myAtoi("-2147483648") == INT_MIN) << endl;
//    cout << (myAtoi("2147483647") == INT_MAX) << endl;
//    cout << (myAtoi("21414") == 21414) << endl;
//    cout << (myAtoi("-21414") == -21414) << endl;
//    cout << myAtoi("-2147483647") << endl;
    return 0;
}

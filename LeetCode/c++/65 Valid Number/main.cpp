// https://leetcode.com/problems/valid-number/

#include <iostream>
#include <vector>

using namespace std;

bool isDigit(char c) {
    return c >= '0' && c <= '9' ;
}

bool isSignCharacter(char c) {
    return c == '-' || c == '+';
}

bool isDot(char c) {
    return c == '.';
}

bool isExponent(char c) {
    return c == 'e' || c == 'E';
}

bool isDigitOrDot(char c) {
    return isDigit(c) || isDot(c);
}

bool isNumber(string s) {
    int i = 0;
    bool hasExponent = false, hasDot = false;
    if (isSignCharacter(s[0])) {
        ++i;
        if (!(i < s.size() && isDigitOrDot(s[i]))) {
            return false;
        }
    }
    for (; i < s.size(); ++i) {
        if (isDigit(s[i])) {

        }
        else if (isSignCharacter(s[i])) {
            return false;
        }
        else if (isDot(s[i])) {
            if (hasExponent || hasDot || !(
                    (i + 1 < s.size() && isDigit(s[i + 1])) || (i - 1 >= 0 && isDigit(s[i - 1]))
                    )) {
                return false;
            }
            hasDot = true;
        }
        else if (isExponent(s[i])) {
            if (hasExponent || i + 1 >= s.size() || !(i - 1 >= 0 && isDigitOrDot(s[i - 1]))) {
                return false;
            }
            if (isSignCharacter(s[i + 1])) {
                ++i;
                if (!(i + 1 < s.size() && isDigit(s[i + 1]))) {
                    return false;
                }
            }
            hasExponent = true;
        }
        else {
            return false;
        }
    }
    return true;
}

int main() {
    cout << isNumber("46.e3") << endl;

    bool check = true;
    vector<string> valid = {"2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789", "46.e3", "-1.0"};
    vector<string> notValid = {"abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53", "+"};

    if (check) {
        cout << "Valid errors:" << endl;
        for (string s: valid) {
            if (!isNumber(s)) {
                cout << s << endl;
            }
        }
        cout << "Not valid errors:" << endl;;
        for (string s: notValid) {
            if (isNumber(s)) {
                cout << s << endl;
            }
        }
    }
    return 0;
}

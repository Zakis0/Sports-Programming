// https://leetcode.com/problems/greatest-common-divisor-of-strings/

#include <iostream>

using namespace std;

int gcd(int a, int b) {
    while (a != 0) {
        if (a >= b) {
            a -= b;
        }
        else {
            b -= a;
        }
    }
    return b;
}

string gcdOfStrings(string str1, string str2) {
    int gcdOfLen = gcd(str1.size(), str2.size());
    string *maxLenStr, *minLenStr;
    bool flag;
    if (str1.size() > str2.size()) {
        maxLenStr = &str1;
        minLenStr = &str2;
    }
    else {
        maxLenStr = &str2;
        minLenStr = &str1;
    }

    string tempStr;
    for (int i = gcdOfLen; i > 0; --i) {
        if (gcdOfLen % i != 0) {
            continue;
        }
        tempStr = "";
        for (int j = 0; j < i; ++j) {
            tempStr += str1[j];
        }
        flag = false;
        for (int j = 0; j < minLenStr->size(); ++j) {
            if (str1[j] != tempStr[j % i] || str2[j] != tempStr[j % i]) {
                flag = true;
                break;
            }
        }
        for (int j = minLenStr->size(); j < maxLenStr->size(); ++j) {
            if ((*maxLenStr)[j] != tempStr[j % i]) {
                flag = true;
                break;
            }
        }
        if (flag) {
            continue;
        }
        return tempStr;
    }
    return "";
}

int main() {
    cout << gcdOfStrings("a", "a") << endl;
//    cout << gcd(16, 12) << endl;
    return 0;
}

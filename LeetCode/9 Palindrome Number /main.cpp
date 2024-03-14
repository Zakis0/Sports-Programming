// https://leetcode.com/problems/palindrome-number/

#include <iostream>
#include <cmath>

using namespace std;

bool isPalindrome(int x) {
    if (x < 0) {
        return false;
    }
    int len = 0, temp = x, firstHalf = 0, halfLen;
    while (temp != 0) {
        ++len;
        temp /= 10;
    }
    halfLen = len / 2;
    for (int i = 0; i < halfLen; ++i) {
        firstHalf += (x % 10) * (int)pow(10, halfLen - i - 1);
        x /= 10;
    }
    if (len % 2 == 1) {
        x /= 10;
    }
    return (firstHalf == x);
}

int main() {
    int n = 345646543;
    cout << isPalindrome(n);
    return 0;
}
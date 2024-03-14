// https://leetcode.com/problems/reverse-integer/

#include <iostream>

using namespace std;

#define INT_MAX 2147483647
#define INT_MIN (-2147483647 - 1)

int reverse(int x) {
    long long result = 0, temp;
    do {
        temp = result * 10 + x % 10;
        if (temp >= INT_MAX || temp <= INT_MIN) {
            return 0;
        }
        result = temp;
        x /= 10;
    } while (x != 0);
    return result;
}

int main() {
    cout << reverse(12344) << endl;
    return 0;
}

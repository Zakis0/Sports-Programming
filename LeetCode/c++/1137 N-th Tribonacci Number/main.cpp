// https://leetcode.com/problems/n-th-tribonacci-number/

#include <iostream>
#include <cmath>

using namespace std;

int tribonacci(int n) {
    int n1 = 0, n2 = 1, n3 = 1, n4 = n1 + n2 + n3;
    if (n == 0) {
        return n1;
    }
    else if (n == 1) {
        return n2;
    }
    else if (n == 2) {
        return n3;
    }
    else if (n == 3) {
        return n4;
    }
    for (int i = 0; i < n - 3; ++i) {
        n1 = n2;
        n2 = n3;
        n3 = n4;
        n4 = n1 + n2 + n3;
    }
    return n4;
}

int main() {
    int n = 25;
    cout << tribonacci(n);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

vector<int> getDivisors(int number) {
    vector<int> commonDivisors;
    for(int i = 2; i * 2 <= number; ++i) {
        if(number % i == 0) {
            commonDivisors.emplace_back(i);
        }
    }
    return commonDivisors;
}

int solve(string s) {
    int aCounter = 0;
    int bCounter = 0;
    for (char c : s) {
        if (c == 'a') {
            ++aCounter;
        }
        else if (c == 'b') {
            ++bCounter;
        }
        if (c == '\n' || c == EOF) {
            break;
        }
    }
    if ((aCounter == 0 or bCounter == 0)) {
        if (s.size() > 1) return 1; else return -1;
    }
    int tempACounter;
    int tempBCounter;
    char c;
    bool flag;
    for (int divisor : getDivisors(s.size())) {
        for (int j = 0; j < s.size() / divisor; ++j) {
            tempACounter = 0;
            tempBCounter = 0;
            flag = true;
            for (int i = 0; i < divisor; ++i) {
                c = s[i + j * divisor];
                if (c == 'a') {
                    ++tempACounter;
                }
                else if (c == 'b') {
                    ++tempBCounter;
                }
            }
            if ((tempACounter == 0) || (tempBCounter == 0) || (aCounter / tempACounter != s.size() / divisor) || (bCounter / tempBCounter != s.size() / divisor)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return divisor;
        }
    }
    return -1;
}

int main() {
    string s;
    cin >> s;
    cout << solve(s);
    return 0;
}

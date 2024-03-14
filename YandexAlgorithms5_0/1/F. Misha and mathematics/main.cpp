#include <bits/stdc++.h>
using namespace std;

const char PLUS = '+';
const char MUL = 'x';

void solve() {
    int n, newInt;

    cin >> n >> newInt;

    bool metOdd = newInt % 2 != 0;

    for(int i = 1; i < n; ++i) {
        cin >> newInt;
        if (!metOdd) {
            cout << PLUS;
        }
        if (!metOdd && newInt % 2 != 0) {
            metOdd = true;
            continue;
        }
        if (!metOdd) {
            continue;
        }
        if (newInt % 2 == 0) {
            cout << PLUS;
        }
        else {
            cout << MUL;
        }
    }
}

int main() {
    solve();
    return 0;
}
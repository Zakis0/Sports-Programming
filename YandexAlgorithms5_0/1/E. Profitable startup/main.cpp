#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, d;
    cin >> n >> k >> d;
    bool flag = true;
    for (int digit = 0; digit < 10; ++digit) {
        if ((n * 10 + digit) % k == 0) {
            n = n * 10 + digit;
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << -1;
        return;
    }
    cout << n;
    for (int i = 0; i < d - 1; ++i) {
        cout << 0;
    }
}

int main() {
    solve();
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

void solve() {
    int numOfLeftRopes, length, maxLength, sum = 0;
    cin >> numOfLeftRopes;
    for (int i = 0; i < numOfLeftRopes; ++i) {
        cin >> length;
        sum += length;
        if (i == 0) {
            maxLength = length;
            continue;
        }
        maxLength = max(maxLength, length);
    }
    if (sum < 2 * maxLength) {
        cout << 2 * maxLength - sum;
    }
    else {
        cout << sum;
    }
}

int main() {
    solve();
    return 0;
}

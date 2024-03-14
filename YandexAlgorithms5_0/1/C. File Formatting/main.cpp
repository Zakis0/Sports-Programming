#include <bits/stdc++.h>
using namespace std;

int getNumOfClicks(int numOfSpaces) {
    int div = numOfSpaces / 4;
    int mod = numOfSpaces % 4;
    if (mod == 3) {
        --mod;
    }
    return div + mod;
}

void solve() {
    int n, a;
    long long int result = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a;
        result += getNumOfClicks(a);
    }
    cout << result;
}

int main() {
    solve();
    return 0;
}

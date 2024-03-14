#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, a, b;
    vector<pair<int, int>> pairs;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        pairs.emplace_back(a, b);
    }
    sort(pairs.begin(), pairs.end(), [](pair<int, int> pair1, pair<int, int> pair2) {
        return pair1.second - pair1.first < pair2.second - pair2.first;
    });
    long long sum = 0;
    int i = 1;
    for (pair<int, int> pair: pairs) {
        sum += (long long)pair.first * (i - 1) + (long long)pair.second * (n - i);
        ++i;
    }
    cout << sum;
}

int main() {
    solve();
    return 0;
}

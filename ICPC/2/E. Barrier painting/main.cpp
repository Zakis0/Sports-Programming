#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, barrierHeight;
    cin >> n;

    vector<int> barrierHeights;

    for (int i = 0; i < n; ++i) {
        cin >> barrierHeight;
        barrierHeights.emplace_back(barrierHeight);
    }
    sort(barrierHeights.begin(), barrierHeights.end());

    int result = barrierHeights.size();
    int s = barrierHeights.size();


    for (int i = 0; i < barrierHeights.size(); ++i) {
        result = min(result, barrierHeights[i] + s - i - 1);
    }
    cout << result;
}

int main() {
    solve();
    return 0;
}

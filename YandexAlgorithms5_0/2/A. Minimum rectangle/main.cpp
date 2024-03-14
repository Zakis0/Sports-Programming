#include <bits/stdc++.h>

using namespace std;

void solve() {
    int k, x, y;

    cin >> k;
    cin >> x >> y;

    int minX = x, maxX = x, minY = y, maxY = y;

    for (int i = 1; i < k; ++i) {
        cin >> x >> y;
        minX = min(x, minX);
        maxX = max(x, maxX);
        minY = min(y, minY);
        maxY = max(y, maxY);
    }
    cout << minX << " " << minY << " " << maxX << " " << maxY;
}

int main() {
    solve();
    return 0;
}

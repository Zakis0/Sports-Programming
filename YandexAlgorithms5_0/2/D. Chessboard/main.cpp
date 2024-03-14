#include <bits/stdc++.h>

using namespace std;

void solve() {
    int numOfSquare, x, y, perimeter = 0;
    cin >> numOfSquare;

    int offsetsX[4] = {-1, 0, 1, 0};
    int offsetsY[4] = {0, 1, 0, -1};

    set<pair<int, int>> sawnOutSet;
    for (int i = 0; i < numOfSquare; ++i) {
        cin >> x >> y;
        sawnOutSet.insert(pair(x, y));
        perimeter += 4;
        for (int j = 0; j < 4; ++j) {
            if (sawnOutSet.contains(pair(x + offsetsX[j], y + offsetsY[j]))) {
                perimeter -= 2;
            }
        }
    }
    cout << perimeter;
}

int main() {
    solve();
    return 0;
}

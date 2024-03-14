#include <bits/stdc++.h>
using namespace std;

int main() {
    int P, V, Q, M;
    cin >> P >> V >> Q >> M;

    int a1 = P - V;
    int b1 = P + V;
    int a2 = Q - M;
    int b2 = Q + M;

    int res = max(b1, b2) - min(a1, a2) + 1;
    res -= max(max(a2 - b1 - 1, a1 - b2 - 1), 0);
    cout << res;
    return 0;
}

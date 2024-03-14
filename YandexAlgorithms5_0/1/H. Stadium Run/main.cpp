#include <bits/stdc++.h>

using namespace std;

const string YES = "YES";
const string NO = "NO";

int Div(int a, int b) {
    if (b == 0) throw b;
    if (a == 0) return 0;
    if (b < 0) {
        a = -a;
        b = -b;
    }
    if (a > 0) return a / b;
    else return -(-a / b) - (-a % b != 0);
}

void solve() {
    cout << setprecision(20);
    int L, x1, v1, x2, v2;
    cin >> L >> x1 >> v1 >> x2 >> v2;

    if (v1 == v2 && v1 == 0 && x1 != x2 && (x1 + x2) % L != 0) {
        cout << NO;
        return;
    }
    cout << YES << endl;
    if ((x2 + x1) % L == 0 || (x2 - x1) % L == 0) {
        cout << 0;
        return;
    }
    int n1 = Div(x1 + x2, -L) + (v1 < -v2);
    double t1 = -(double)(x1 + x2 + n1 * L) / (v1 + v2);
    int n2 = Div(x1 - x2, L) + (v1 >= v2);
    double t2 = (double)(x2 - x1 + n2 * L) / (v1 - v2);
    cout << min(t1, t2);
}

int main() {
    solve();
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

deque<int> dq;

int a, b;

void printAB() {
    cout << a << " " << b << endl;
}

vector<int> createArr(int n) {
    int input;
    vector<int> arr;
    for (int i = 0; i < n; ++i) {
        cin >> input;
        arr.push_back(input);
    }
    return arr;
}

void fillDq(vector<int> arr, int n) {
    for (int i = 0; i < n; ++i) {
        dq.push_back(arr[i]);
    }
}

void printDq() {
    for (int i : dq) {
        cout << i << " ";
    }
    cout << endl;
}

void operation() {
    a = dq.front();
    dq.pop_front();
    b = dq.front();
    dq.pop_front();
    if (a > b) {
        dq.push_front(a);
        dq.push_back(b);
    }
    else {
        dq.push_front(b);
        dq.push_back(a);
    }
}

void operationN(ll n) {
    if (n == 0) {
        a = dq.front();
        b = dq.back();
    }
    for (int i = 0; i < n; ++i) {
        operation();
    }
}

int findMaxPos(const vector<int>& arr) {
    int m = dq.front(), maxPos = 0, curPos = 0;
    for (int el : arr) {
        if (el > m) {
            m = el;
            maxPos = curPos;
        }
        ++curPos;
    }
    return maxPos;
}

void task(int maxPos, int sycleLen) {
    ll m;
    cin >> m;

    if (m >= maxPos) {
        operationN(maxPos);
        operationN((m - maxPos) % sycleLen);
    } else {
        operationN(m);
    }
    printAB();
}

void solve() {
    int n, q, maxPos, sycleLen;
    vector<int> arr;

    cin >> n >> q;

    sycleLen = n - 1;
    arr = createArr(n);
    maxPos = findMaxPos(arr);

    for (int i = 0; i < q; ++i) {
        dq.clear();
        fillDq(arr, n);
        task(maxPos, sycleLen);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
    solve();
    return 0;
}
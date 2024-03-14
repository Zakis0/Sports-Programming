#include <bits/stdc++.h>

using namespace std;

long long int getSumOfNGeometricProgression(long long int n, int q) {
    if (q == 1) return n;
    return (long long int)((pow(q, n) - 1) / (q - 1));
}

long long int getHeight(int k, long long int value) {
    if (k == 1) return value;
    long long int height = 0;
    while (true) {
        if (getSumOfNGeometricProgression(++height, k) >= value) {
            break;
        }
    }
    return height;
}

long long int getGroupNumByHeight(int k, long long int value, long long int height) {
    return (value - getSumOfNGeometricProgression(height - 1, k) - 1) / k;
}
long long int getParentNumber(int k, long long int value, long long int height) {
    if (height == 1) return 0;
    return getGroupNumByHeight(k, value, height) + getSumOfNGeometricProgression(height - 2, k) + 1;
}

void solve(int k, int q) {
    long long int node1, node2;
    for (int i = 0; i < q; ++i) {
        cin >> node1;
        cin >> node2;

        long long int node1Heigth = getHeight(k, node1);
        long long int node2Heigth = getHeight(k, node2);

        long long int counter = 0;
        while (node1 != node2) {
            if (node1 < node2) {
                node2 = getParentNumber(k, node2, node2Heigth--);
            }
            else {
                node1 = getParentNumber(k, node1, node1Heigth--);
            }
            ++counter;
        }
        cout << counter << endl;
    }
}

void consoleInput() {
    long long int n;
    int k, q;
    cin >> n;
    cin >> k;
    cin >> q;
    solve(k, q);
}

int main() {
    consoleInput();
}

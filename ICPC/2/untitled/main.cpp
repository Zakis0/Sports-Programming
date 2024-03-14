#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int K = 100000;

const int DIV_CONST = 998244353;

set<pair<int, int>> cordToCheck;

int exist;

void printCord(pair<int, int> n) {
    cout << n.first << " " << n.second << endl;
}

void printArr(array<pair<int, int>, K> arr, int n) {
    int i = 0;
    for (pair<int, int> el : arr) {
        if (i == n) {
            break;
        }
        printCord(el);
        ++i;
    }
    cout << endl;
}


void printSet(set<pair<int, int>> st) {
    for (pair<int, int> el : st) {
        cout << el.first << " " << el.second << endl;
    }
    cout << endl;
}

bool existNeib(array<pair<int, int>, K> cordArr, pair<int, int> cord, int n) {
    int i = 1;
    for (pair<int, int> c : cordArr) {
        if (i == n) {
            break;
        }
        ++i;
        if (c == cord) {
            continue;
        }
        if ((c.first == cord.first + 1 && c.second == cord.second) ||
            (c.first == cord.first - 1 && c.second == cord.second) ||
            (c.first == cord.first && c.second == cord.second + 1) ||
            (c.first == cord.first && c.second == cord.second - 1)) {
            return true;
        }
    }
    return false;
}

void findNeib(array<pair<int, int>, K> cordArr, pair<int, int> cord, int n) {
    exist = 1;
    if (existNeib(cordArr, cord, n)) {
        cordToCheck.erase(cord);
        if (cordToCheck.count({cord.first + 1, cord.second})) findNeib(cordArr, {cord.first + 1, cord.second}, n);
        if (cordToCheck.count({cord.first - 1, cord.second})) findNeib(cordArr, {cord.first - 1, cord.second}, n);
        if (cordToCheck.count({cord.first, cord.second + 1})) findNeib(cordArr, {cord.first, cord.second + 1}, n);
        if (cordToCheck.count({cord.first, cord.second - 1})) findNeib(cordArr, {cord.first, cord.second - 1}, n);
    }
}

void solve() {
    int k, x, y, numOfGroups = 0;
    array<pair<int, int>, K> cordArr;

    cin >> k;

    for(int i = 0; i < k; ++i) {
        cin >> x >> y;
        cordArr[i] = {x, y};
        cordToCheck.insert({x, y});
    }
    for (;cordToCheck.size() != 0;) {
        for (pair<int, int> c : cordToCheck) {
            exist = 0;

            cordToCheck.erase(c);

            findNeib(cordArr, c, k);
            if (exist) {
                ++numOfGroups;
            }
            break;
        }
    }
    cout << (pow (2.0, numOfGroups)) << endl;
}

int main() {
//    freopen("input.txt", "r", stdin);
    solve();
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

const string PUSH = "push";
const string POP = "pop";

int getNextMin(const vector<int>& arr, int lastMin) {
    int min;
    bool exist = false;
    for (int i : arr) {
        if (i > lastMin) {
            min = i;
            exist = true;
            break;
        }
    }
    if (!exist) return lastMin;
    for (int i : arr) {
        if (i < min && i > lastMin) {
            min = i;
        }
    }
    return min;
}

int getMin(vector<int> arr) {
    int m = arr[0];
    for (int i : arr) {
        m = min(i, m);
    }
    return m;
}

vector<pair<int, int>> getIndexedArr(vector<int> arr, int n) {
    vector<pair<int, int>> inputWithIndexes(n);
    int curMin = getMin(arr), lastMin;
    int order = 0;
    while (true) {
        for (int j = 0; j < n; ++j) {
            if (arr[j] == curMin) {
                inputWithIndexes[j] = {arr[j], order};
                ++order;
            }
        }
        lastMin = curMin;
        curMin = getNextMin(arr, curMin);
        if (curMin == lastMin) {
            break;
        }
    }
    return inputWithIndexes;
}

void solve() {
    int n, curIndex = 0;

    cin >> n;

    vector<int> input(n);
    vector<pair<int, int>> inputWithIndexes(n);
    vector<string> strArr;

    vector<pair<int, int>> st;

    for (int i = 0; i < n; ++i) {
        cin >> input[i];
    }
    inputWithIndexes = getIndexedArr(input, n);

    for (pair<int, int> i : inputWithIndexes) {
        st.push_back(i);
        strArr.push_back(PUSH);
        while (st.back().second == curIndex) {
            st.pop_back();
            strArr.push_back(POP);
            ++curIndex;
        }
    }
    if (!st.empty()) {
        cout << "impossible" << endl;
    }
    else {
        for (const string& str: strArr) {
            cout << str << endl;
        }
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
    solve();
    return 0;
}
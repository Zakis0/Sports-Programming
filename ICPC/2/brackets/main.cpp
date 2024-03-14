#include <bits/stdc++.h>

using namespace std;

char getPair(char c) {
    if (c == '{') {
        return '}';
    }
    if (c == '[') {
        return ']';
    }
    if (c == '(') {
        return ')';
    }
    return ' ';
}

bool isOpenBracket(char c) {
    if (c == '{' || c == '[' || c == '(') {
        return true;
    }
    return false;
}

void solve() {
    int i = 0;

    string str;
    vector<pair<char, int>> st;

    cin >> str;

    vector<int> res(str.length());

    if (isOpenBracket(str[i])) {
        st.emplace_back(str[i], i);
        ++i;
    }
    else {
        cout << -1 << endl;
        return;
    }
    for (int j = 0; j < str.length() - 1; ++j) {
        if (!isOpenBracket(str[i]) && getPair(st.back().first) != str[i]) {
            cout << -1 << endl;
            return;
        }
        if (isOpenBracket(str[i])) {
            st.emplace_back(str[i], i);
        }
        else {
            res[st.back().second] = i;
            res[i] = st.back().second;
            st.pop_back();
        }
        ++i;
    }
    if (!st.empty()) {
        cout << -1 << endl;
        return;
    }
    for (int k = 0; k < str.length(); ++k) {
        cout << res[k] << " ";
    }
}

int main() {
    solve();
    return 0;
}

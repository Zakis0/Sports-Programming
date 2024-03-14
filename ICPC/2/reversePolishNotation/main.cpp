#include <bits/stdc++.h>

using namespace std;

vector<int> st;

bool isOperation(string op) {
    return op == "+" || op == "-" || op == "*" || op == "/";
}

int strToInt(string str) {
    int len = str.length();
    int res = 0;
    for (int i = 0; i < len - 1; ++i) {
        res = (res + (str[i] - '0')) * 10;
    }
    res += str[len - 1] - '0';
    return res;
}

void solve() {
    string str, op;
    int a, b;
    for (;true;) {
        cin >> str;
        if (isOperation(str)) {
            if (st.size() < 2) {
                cout << st.back() << endl;
                st.pop_back();
                break;
            }
            else {
                op = str;
                a = st.back();
                st.pop_back();
                b = st.back();
                st.pop_back();
                if (op == "+") {
                    st.push_back(b + a);
                }
                else if (op == "-") {
                    st.push_back(b - a);
                }
                else if (op == "*") {
                    st.push_back(b * a);
                }
                else if (op == "/") {
                    st.push_back(b / a);
                }
            }

        }
        else {
            st.push_back(strToInt(str));
        }
    }
}

int main() {
//    freopen("input.txt","r",stdin);
    solve();
    return 0;
}
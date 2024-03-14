// https://leetcode.com/problems/valid-parentheses/

#include <iostream>
#include <stack>

using namespace std;

char getPair(char c) {
    switch (c) {
        case ')': {
            return '(';
        }
        case ']': {
            return '[';
        }
        case '}': {
            return '{';
        }
        default: {
            return '_';
        }
    }
}

bool isValid(string s) {
    stack<char> st;
    for (char c: s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        }
        else {
            if (st.size() > 0 && st.top() == getPair(c)) {
                st.pop();
            }
            else {
                return false;
            }
        }
    }
    return st.empty();
}

int main() {
    string str = "}";
    cout << isValid(str) << endl;
    return 0;
}

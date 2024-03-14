#include <bits/stdc++.h>

using namespace std;

const string PUSH = "push";
const string MAX = "max";
const string POP = "pop";

const int MAX_SIZE = 400001;

struct Stack {
    int size = 0;
    int stackMax;
    int st[MAX_SIZE];

    void pop() {
        if (!empty()) {
            --size;
            if (!empty()) {
                stackMax = back();
            }
        }
    }
    int back() const {
        return st[size - 1];
    }
    void emplace_back(int value) {
        if (empty()) {
            stackMax = value;
        }
        else {
            stackMax = max(value, stackMax);
        }
        st[size++] = stackMax;
    }
    bool empty() const {
        return size == 0;
    }
    void printMax() const {
        if (!empty()) {
            cout << stackMax << endl;
        }
    }
};

void solve() {
    int q, value;
    string command;

    Stack stack;

    cin >> q;

    for(int i = 0; i < q; ++i) {
        cin >> command;
        if (command == PUSH) {
            cin >> value;
            stack.emplace_back(value);
        }
        else if (command == POP) {
            stack.pop();
        }
        else if (command == MAX) {
            stack.printMax();
        }
    }
}

int main() {
    solve();
    return 0;
}
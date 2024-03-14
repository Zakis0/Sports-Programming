#include <bits/stdc++.h>

#define MAX_HEIGHT 32

using namespace std;

int getBit(int num, int position) {
    int mask = 1 << position;
    return (num & mask) != 0;
}

struct Node {
    Node* left;
    Node* right;
    Node* parent;
    int value;
    int bit;
    int leftValue, rightValue;
    int height;

    Node() {
        left = nullptr;
        right = nullptr;
        value = -1;
        bit = -1;
        parent = nullptr;
        leftValue = -1;
        rightValue = -1;
        height = 0;
    }
    ~Node() {
        delete left;
        delete right;
    }
    void back(int value, bool isLeft, bool stop = 0) {
        if (isLeft) {
            leftValue = value;
        }
        else {
            rightValue = value;
        }
        if (parent == nullptr) {
            return;
        }
        int newIsLeft = parent->left == this;
        if ((newIsLeft && parent->right != nullptr) || (!newIsLeft && parent->left != nullptr)) {
            stop = true;
        }
        parent->back(value, newIsLeft, stop);
    }

    bool add(int value, int& maxHeight, int height = 0) {
        if (height == MAX_HEIGHT) {
            parent->back(value, parent->left == this);
            return false;
        }
        int bit = getBit(value, MAX_HEIGHT - 1 - height);
        Node* newNode = new Node;
        newNode->value = value;
        newNode->height = height + 1;
        newNode->bit = bit;
        newNode->parent = this;
        if (bit == 0) {
            if (left != nullptr) {
                if (height == MAX_HEIGHT - 1) {
                    return true;
                }
                newNode = left;
            }
            else {
                left = newNode;
            }
            if (right != nullptr) {
                maxHeight = max(maxHeight, height);
            }
        }
        else {
            if (right != nullptr) {
                if (height == MAX_HEIGHT - 1) {
                    return true;
                }
                newNode = right;
            }
            else {
                right = newNode;
            }
            if (left != nullptr) {
                maxHeight = max(maxHeight, height);
            }
        }
        return newNode->add(value, maxHeight, height + 1);
    }
};

vector<Node*> bestNodes;

int bfsGetXOrArg(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    if (node->height == MAX_HEIGHT) {
        return node->value;
    }
    if (node->left != nullptr) {
        return bfsGetXOrArg(node->left);
    }
    if (node->right != nullptr) {
        return bfsGetXOrArg(node->right);
    }
    return -1;
}

void bfsToMaxHeight(Node* node, int& maxHeight, vector<int>& xOrs) {
    if (node->height == maxHeight) {
        int value1 = node->leftValue;
        int value2 = node->rightValue;
//        int value1 = bfsGetXOrArg(node->left);
//        int value2 = bfsGetXOrArg(node->right);
        if (value1 == -1 || value2 == -1) {
            return;
        }
        xOrs.emplace_back(value1 ^ value2);
        return;
    }
    if (node->left != nullptr) {
        bfsToMaxHeight(node->left, maxHeight, xOrs);
    }
    if (node->right != nullptr) {
        bfsToMaxHeight(node->right, maxHeight, xOrs);
    }
}

int testGetMinXOr(const vector<int>& values) {
    int maxHeight = 0;
    Node* root = new Node;
    for (int i = 0; i < values.size(); ++i) {
        bool existedValue = root->add(values[i], maxHeight);
        if (existedValue) {
            delete root;
            return 0;
        }
    }
    vector<int> xOrs;
    bfsToMaxHeight(root, maxHeight, xOrs);
    if (!xOrs.empty()) {
        int m = min_element(xOrs.begin(), xOrs.end())[0];
        delete root;
        return m;
    }
    else {
        xOrs.clear();
        delete root;
        return -1;
    }
}

void solve() {
    int T, n;
    cin >> T;

    bool cont = false;
    for (int k = 0; k < T; ++k) {
        cin >> n;
        int maxHeight = 0;
        cont = false;
        Node* root = new Node;
        for (int i = 0; i < n; ++i) {
            int value;
            cin >> value;
            bool existedValue = root->add(value, maxHeight);
            if (existedValue) {
                cout << 0 << endl;
                cont = true;
                break;
            }
        }
        if (cont) {
            delete root;
            continue;
        }
        vector<int> xOrs;
        bfsToMaxHeight(root, maxHeight, xOrs);
        if (!xOrs.empty()) {
            cout << min_element(xOrs.begin(), xOrs.end())[0] << endl;
        }
        else {
            cout << -1 << endl;
        }
        delete root;
        xOrs.clear();
    }
}

int getRand(int max) {
    return (rand()) % max;
}

void test() {
    int maxValue = 3;
    int n = 2;
    vector<int> values;

    for (int i = 0; i < n; ++i) {
        values.emplace_back(getRand(maxValue));
    }
//    values = {0, 1};
    int m = INT32_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            m = min(m, values[i] ^ values[j]);
        }
    }
    int res = testGetMinXOr(values);
    if (m != res) {
        cout << "+++++++++++++" << endl;
        cout << "Error ";
        cout << "True: " << m << " My: " << res << endl;
        for (int value: values) {
            cout << value << " ";
        }
        cout << endl;
        cout << "---------" << endl;
    }

}

void startTests() {
    srand(time(nullptr));
    int numOfTest = 100;
    for (int i = 0; i < numOfTest; ++i) {
        test();
    }
}

int main() {
    solve();
//    startTests();
    return 0;
}
//189 188
//
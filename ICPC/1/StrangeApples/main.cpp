#include <bits/stdc++.h>
using namespace std;

struct Apple {
    int dec;
    int inc;
    int pos;

    int impact = 0;
    Apple() {
        this->dec = -1;
        this->inc = -1;
        this->pos = -1;
        impact = inc - dec;
    }
    Apple(int dec, int inc, int pos) {
        this->dec = dec;
        this->inc = inc;
        this->pos = pos;
        impact = inc - dec;
    }
    bool operator<(Apple const& obj) const {
        if (impact >= 0 && obj.impact >= 0) {
            if (dec == obj.dec) {
                return inc < obj.inc;
            }
            return dec > obj.dec;
        }
        if (impact < 0 && obj.impact < 0) {
            return inc < obj.inc;
        }
        return impact < 0;
    }
    bool operator>(Apple const& obj) const {
        return obj < *this;
    }
    friend ostream& operator<<(ostream &os, const Apple &apple){
        return os << "dec: " << apple.dec <<
                  "\t\tinc: " << apple.inc <<
                  "\t\timpact: " << apple.impact <<
                  "\t\tpos: " << apple.pos;
    }
};

void solve() {
    int n, s;
    cin >> n;
    cin >> s;

    vector<int> answer;
    vector<Apple> resultAppleOrder;
    int dec, inc;
    for (int i = 0; i < n; ++i) {
        cin >> dec;
        cin >> inc;
        resultAppleOrder.emplace_back(dec, inc, i + 1);
    }
    std::sort(resultAppleOrder.begin(), resultAppleOrder.end(), greater<>());
    for (Apple apple: resultAppleOrder) {
        s -= apple.dec;
        if (s <= 0) {
            cout << -1;
            return;
        }
        s += apple.inc;
        answer.emplace_back(apple.pos);
    }
    for (int pos: answer) {
        cout << pos << " ";
    }
}

void test() {
    vector<Apple> vec;

    int MAX = 7;
    int MIN = 1;
    for (int dec = MIN; dec < MAX; ++dec) {
        for (int inc = MIN; inc < MAX; ++inc) {
            vec.emplace_back(dec, inc, 0);
        }
    }
    std::sort(vec.begin(), vec.end(), greater<>());

    for (Apple apple: vec) {
        cout << apple << endl;
    }
}

int main() {
    solve();
//    test();
    return 0;
}
//2 6
//3 2
//5 3

//3 2 impact = -1
//5 3 impact = -2

//2 6
//3 2
//4 1

//3 2 impact = -1
//4 1 impact = -3

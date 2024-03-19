#include <bits/stdc++.h>
using namespace std;

struct Berry {
    int dec;
    int inc;
    int pos;

    int impact = 0;
    Berry() {
        this->dec = -1;
        this->inc = -1;
        this->pos = -1;
        impact = inc - dec;
    }
    Berry(int dec, int inc, int pos) {
        this->dec = dec;
        this->inc = inc;
        this->pos = pos;
        impact = inc - dec;
    }
    bool operator>(Berry const& obj) const {
        if (impact > 0 && obj.impact <= 0 ||
            impact == 0 && obj.impact < 0) {
            return true;
        }
        if (impact > 0 && obj.impact > 0) {
            if (dec == obj.dec) {
                return inc > obj.inc;
            }
            return dec < obj.dec;
        }
        if (impact < 0 && obj.impact < 0 ||
            impact == 0 && obj.impact == 0) {
            if (inc == obj.inc) {
                return dec < obj.dec;
            }
            return inc > obj.inc;
        }
        return false;
    }
    bool operator<(Berry const& obj) const {
        return obj > *this;
    }
    friend ostream& operator<<(ostream &os, const Berry &apple){
        return os << "dec: " << apple.dec <<
                  "\t\tinc: " << apple.inc <<
                  "\t\timpact: " << apple.impact <<
                  "\t\tpos: " << apple.pos;
    }
};

void test() {
    int MAX = 3;
    vector<Berry> resultBerryOrder;
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            resultBerryOrder.emplace_back(i, j, 0);
        }
    }
    sort(resultBerryOrder.begin(), resultBerryOrder.end(), greater<>());
    for (Berry berry: resultBerryOrder) {
        cout << berry << endl;
    }
}

void solve() {
    int n;
    long long height = 0, maxHeight = 0;
    cin >> n;

    vector<int> answer;
    vector<Berry> resultBerryOrder;
    int dec, inc;
    for (int i = 0; i < n; ++i) {
        cin >> inc;
        cin >> dec;
        resultBerryOrder.emplace_back(dec, inc, i + 1);
    }
    sort(resultBerryOrder.begin(), resultBerryOrder.end(), greater<>());
    for (Berry berry: resultBerryOrder) {
        height += berry.inc;
        maxHeight = max(maxHeight, height);
        height -= berry.dec;
        answer.emplace_back(berry.pos);
    }
    cout << maxHeight << endl;
    for (int pos: answer) {
        cout << pos << " ";
    }
}

int main() {
    solve();
//    test();
    return 0;
}

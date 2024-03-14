// https://leetcode.com/problems/first-bad-version/

#include <iostream>

using namespace std;

int bad;

bool isBadVersion(int version) {
    return version >= bad;
}

int findRec(int start, int end) {
    if (start == 1 && end <= 2) {
        if (isBadVersion(1)) {
            return 1;
        }
        else {
            return 2;
        }
    }
    if (start + 1 == end) {
        return start + 1;
    }
    if (isBadVersion(start + ((end - start) / 2))) {
        findRec(start, start + ((end - start) / 2));
    }
    else {
        findRec(start + ((end - start) / 2), end);
    }
}

int firstBadVersion(int n) {
    return findRec(1, n);
}

int main() {
//    cout << firstBadVersion(100) << endl;

    bool check = true;

    if (check) {
        for (int i = 1; i < 10000000; ++i) {
            bad = i;
            if (firstBadVersion(10000000) != bad) {
                cout << i << endl;
            }
        }
    }
    return 0;
}

// https://leetcode.com/problems/zigzag-conversion/

#include <iostream>

using namespace std;

/*
 * 1 - 0
 * 2 - 1
 * 3 - 3
 * 4 - 5
 * 5 - 7
 */

int getNumOfSkippedRow(int n) {
    if (n == 1) {
        return 0;
    }
    return 2 * (n - 1) - 1;
}


string convert(string s, int numRows) {
    int numOfSkip = getNumOfSkippedRow(numRows);
    string result = "";
    for (int row = 0; row < numRows; ++row) {
        for (int i = row; i < s.size(); i += numOfSkip + 1 - row) {
            cout << row << " " << i << endl;
            result += s[i];
        }
    }
    return result;
}

/*
 * 0 -> 0
 * 1 -> 4
 * 2 -> 1
 * 3 -> 5
 * 4 -> 2
 * 5 -> 6
 * 6 -> 3
 * 7 -> 7
 */

int main() {
//    cout << convert("asasasas", 2) << endl;
    cout << convert("PAYPALISHIRING", 3) << endl;
    cout << "PAHNAPLSIIGYIR" << endl;
    return 0;
}

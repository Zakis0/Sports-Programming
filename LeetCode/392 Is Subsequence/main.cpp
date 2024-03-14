#include <iostream>

using namespace std;

bool isSubsequence(string s, string t) {
    int i = 0, numOfCheckedLetters = 0, tSize = t.size(), sSize = s.size();
    if (s.empty()) {
        return true;
    }
    for (char c: s) {
        while (i < tSize) {
            if (c == t[i++]) {
                if (++numOfCheckedLetters == sSize) {
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

int main() {
    string s1 = "";
    string s2 = "ahbgdc";
    cout << isSubsequence(s1, s2) << endl;
    return 0;
}

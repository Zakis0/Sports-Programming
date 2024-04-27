// https://leetcode.com/problems/verifying-an-alien-dictionary/

#include <iostream>
#include <vector>

using namespace std;

bool s1LessThenS2(string s1, string s2, const int* alphabet) {
    for (int i = 0; i < min(s1.size(), s2.size()); ++i) {
        if (alphabet[s2[i]] < alphabet[s1[i]]) {
            return false;
        }
        else if (alphabet[s2[i] - 'a'] > alphabet[s1[i] - 'a']) {
            return true;
        }
    }
    if (s1.size() > s2.size()) {
        return false;
    }
    return true;
}

bool isAlienSorted(vector<string>& words, string order) {
    int* alphabet = new int[order.size()];
    for (int i = 0; i < order.size(); ++i) {
        alphabet[order[i] - 'a'] = i;
    }
    for (int i = 0; i < words.size() - 1; ++i) {
        if (!s1LessThenS2(words[i], words[i + 1], alphabet)) {
            delete[] alphabet;
            return false;
        }
    }
    delete[] alphabet;
    return true;
}

int main() {
    vector<string> vec = {"abcc","abc"};
    cout << isAlienSorted(vec, "abcdefghijklmnopqrstuvwxyz") << endl;
    return 0;
}

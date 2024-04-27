// https://leetcode.com/problems/isomorphic-strings/

#include <iostream>
#include <map>

using namespace std;

bool isIsomorphic(string s, string t) {
    map<char, int> dict1, dict2;
    if (s.size() != t.size()) {
        return false;
    }
    for (int i = 0; i < s.size(); ++i) {
        if (dict1.find(s[i]) == dict1.end()) {
            dict1[s[i]] = dict1.size();
        }
        if (dict2.find(t[i]) == dict2.end()) {
            dict2[t[i]] = dict2.size();
        }
        if (dict1[s[i]] != dict2[t[i]]) {
            return false;
        }
    }
    return true;
}

int main() {
    string s1 = "foo";
    string s2 = "bar";
    cout << isIsomorphic(s1, s2) << endl;
    return 0;
}

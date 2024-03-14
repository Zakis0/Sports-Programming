#include <iostream>
#include <vector>

using namespace std;

#define MAX_STR_LENGTH 200

string longestCommonPrefix(vector<string>& strs) {
    string result;
    char c;
    for (int i = 0; i < MAX_STR_LENGTH; ++i) {
        if (i >= strs[0].size()) {
            return result;
        }
        c = strs[0][i];
        for (int j = 1; j < strs.size(); ++j) {
            if (i >= strs[j].size() || c != strs[j][i]) {
                return result;
            }
        }
        result += c;
    }
    return result;
}

int main() {
    vector<string> strs = {"cog","","car"};
    cout << longestCommonPrefix(strs) << endl;
    return 0;
}
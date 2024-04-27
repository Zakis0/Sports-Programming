// https://leetcode.com/problems/roman-to-integer/

#include <iostream>
#include <map>

using namespace std;

//int charToInt(string& s, int& i) {
//    switch (s[i]) {
//        case 'I': {
//            if (s[i + 1] == 'V') {
//                return 4;
//            }
//            else if (s[i + 1] == 'X') {
//                return 9;
//            }
//            else {
//                --i;
//                return 1;
//
//            }
//        }
//        case 'V': {
//            --i;
//            return 5;
//        }
//        case 'X': {
//            if (s[i + 1] == 'L') {
//                return 40;
//            }
//            else if (s[i + 1] == 'C') {
//                return 90;
//            }
//            else {
//                --i;
//                return 10;
//            }
//        }
//        case 'L': {
//            --i;
//            return 50;
//        }
//        case 'C': {
//            if (s[i + 1] == 'D') {
//                return 400;
//            }
//            else if (s[i + 1] == 'M') {
//                return 900;
//            }
//            else {
//                --i;
//                return 100;
//            }
//        }
//        case 'D': {
//            --i;
//            return 500;
//        }
//        case 'M': {
//            --i;
//            return 1000;
//        }
//        default: {
//
//        }
//    }
//    return 0;
//}
//
//int romanToInt(string s) {
//    int result = 0, i = 0;
//    for (; i < s.size() - 1; i += 2) {
//        result += charToInt(s, i);
//    }
//    if (i == s.size() - 1) {
//        s += 'Q';
//        result += charToInt(s, i);
//    }
//    return result;
//}

int romanToInt(string s) {
    int result = 0;
    map<char, int> dict = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000},
    };
    for (int i = 0; i < s.size() - 1; ++i) {
        if (dict[s[i]] < dict[s[i + 1]]) {
            result -= dict[s[i]];
        }
        else {
            result += dict[s[i]];
        }
    }
    return result + dict[s[s.size() - 1]];
}

int main() {
    string str = "MCMXCIV";
    cout << romanToInt(str);
    return 0;
}

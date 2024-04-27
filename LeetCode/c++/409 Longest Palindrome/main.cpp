// https://leetcode.com/problems/longest-palindrome/

#include <iostream>

using namespace std;

//#define ALPHABET_LENGTH 52

//bool isLowerCase(char c) {
//    return c >= 'a' && c <= 'z';
//}
//
//int longestPalindrome(string s) {
//    int arr[ALPHABET_LENGTH];
//    int len = 0;
//    bool hasNotEvenNumOfChar = false;
//    for (int& i : arr) {
//        i = 0;
//    }
//    for (char c: s) {
//        if (isLowerCase(c)) {
//            arr[c - 'a'] += 1;
//        }
//        else {
//            arr[c - 'A' + 'z' - 'a' + 1] += 1;
//        }
//    }
//    for (int i : arr) {
//        if (i % 2 == 1) {
//            hasNotEvenNumOfChar = true;
//        }
//        len += (i / 2) * 2;
//    }
//    if (hasNotEvenNumOfChar) {
//        len += 1;
//    }
//    return len;
//}

int longestPalindrome(string s) {
    int arr[(int)('z' + 1)]{};
    int counter = 0;
    for (char c: s) {
        ++arr[c];
    }
    for (int i : arr) {
        counter += i & 1;
    }
    return s.size() - counter + (counter > 0);
}

int main() {
    cout << longestPalindrome("aaabba") << endl;
    return 0;
}

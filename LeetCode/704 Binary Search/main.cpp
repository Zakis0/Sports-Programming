// https://leetcode.com/problems/binary-search/

#include <iostream>
#include <vector>

using namespace std;

int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (nums[middle] == target) {
            return middle;
        }
        if (nums[middle] < target) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }
    return -1;
}

int main() {
    vector<int> vec {-1};
    cout << search(vec, 2) << endl;
    return 0;
}

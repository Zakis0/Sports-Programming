// https://leetcode.com/problems/find-pivot-index/

#include <iostream>
#include <vector>

using namespace std;

int pivotIndex(vector<int>& nums) {
    int leftSum = 0, rightSum = 0;
    for (int i = 1; i < nums.size(); ++i) {
        rightSum += nums[i];
    }
    for (int i = 0; i < nums.size() - 1; ++i) {
        if (leftSum == rightSum) {
            return i;
        }
        leftSum += nums[i];
        rightSum -= nums[i + 1];
    }
    if (leftSum == rightSum) {
        return nums.size() - 1;
    }
    return -1;
}

int main() {
    vector<int> nums = {-1,-1,0,1,1,0};
    cout << pivotIndex(nums) << endl;
    return 0;
}

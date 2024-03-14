// https://leetcode.com/problems/running-sum-of-1d-array/

#include <iostream>
#include <vector>

using namespace std;

vector<int> runningSum(vector<int>& nums) {
    vector<int> result;
    result.push_back(nums[0]);
    for (int i = 1; i < nums.size(); ++i) {
        result.push_back(result[i - 1] + nums[i]);
    }
    return result;
}

int main() {
    vector<int> nums = {1,1,1,1,1};
    for (int i: runningSum(nums)) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

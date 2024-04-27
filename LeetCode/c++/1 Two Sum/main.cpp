// https://leetcode.com/problems/two-sum/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    map<int, int> dict;
    for (int i = 0; i < nums.size(); ++i) {
        if (dict.find(target - nums[i]) != dict.end()) {
            return {dict[target - nums[i]], i};
        }
        dict[nums[i]] = i;
    }
}

int main() {
    int target = 0;
    vector<int> nums = {-3,3};
    vector<int> result = twoSum(nums, target);
    cout << result[0] << " " << result[1];
    return 0;
}

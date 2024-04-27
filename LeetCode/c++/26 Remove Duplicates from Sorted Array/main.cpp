// https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/

#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int>& vec, int start = 0, int end = -1) {
    if (end == -1) {
        end = vec.size();
    }
    for (int i = start; i < end; ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int removeDuplicates(vector<int>& nums) {
    int j = 1;
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i - 1] != nums[i]) {
            nums[j++] = nums[i];
        }
    }
    return j;
}

int main() {
    vector<int> vec = {1, 1, 2};
    int dub = removeDuplicates(vec);
    cout << dub << endl;
    printVector(vec, 0, dub);
    return 0;
}

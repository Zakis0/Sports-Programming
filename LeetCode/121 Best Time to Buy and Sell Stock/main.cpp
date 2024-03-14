// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

#include <iostream>
#include <vector>

using namespace std;

int maxProfit(vector<int>& prices) {
    int toBuy = prices[0];
    int profit = 0;
    for (int i = 0; i < prices.size(); ++i) {
        if (prices[i] < toBuy) {
            toBuy = prices[i];
            continue;
        }
        if (prices[i] - toBuy > profit) {
            profit = prices[i] - toBuy;
        }
    }
    if (profit > 0) {
        return profit;
    }
    return 0;
}

int main() {
    vector<int> vec = {};
    cout << maxProfit(vec) << endl;
    return 0;
}

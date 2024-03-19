#include <bits/stdc++.h>

using namespace std;

void solve() {
    int numOfDays, timeToDeterioration, price, profit = 0;
    cin >> numOfDays >> timeToDeterioration;
    int curDayMinPrice[numOfDays];
    fill(curDayMinPrice, curDayMinPrice + numOfDays, INT32_MAX);
    for (int i = 0; i < numOfDays; ++i) {
        cin >> price;
        for (int j = 0; j < timeToDeterioration + 1 && i + j < numOfDays; ++j) {
            curDayMinPrice[i + j] = min(curDayMinPrice[i + j], price);
        }
        profit = max(profit, price - curDayMinPrice[i]);
    }
    cout << max(0, profit);
}

int main() {
    solve();
    return 0;
}

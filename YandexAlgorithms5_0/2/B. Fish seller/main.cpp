#include <bits/stdc++.h>

using namespace std;

void solve() {
    int numOfDays, timeToDeterioration, deterioration, price, profit;
    cin >> numOfDays >> timeToDeterioration;
    int curDayMinPrice[numOfDays];
    for (int i = 0; i < numOfDays; ++i) {
        cin >> price;
        if (i == 0) {
            curDayMinPrice[i] = price;
            continue;
        }
        if (i > timeToDeterioration) {
            curDayMinPrice[i - timeToDeterioration] = INT32_MAX;
        }
        curDayMinPrice[i] = min(price, curDayMinPrice[i - 1]);
        profit = max(profit, price - curDayMinPrice[i - 1]);
    }
    cout << max(0, profit);
}

int main() {
    solve();
    return 0;
}

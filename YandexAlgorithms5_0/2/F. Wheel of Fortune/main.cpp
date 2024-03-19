#include <bits/stdc++.h>

using namespace std;

int modAbs(int value, int mod) {
    return (value % mod + mod) % mod;
}

void getMaxProfit(long long& speed, long long& speedReduction, int& maxProfit, int sectorValues[], int& numOfSectors) {
    long long sectorIndex = (speed - 1) / speedReduction;
    maxProfit = max(maxProfit, sectorValues[modAbs((int)sectorIndex, numOfSectors)]);
    maxProfit = max(maxProfit, sectorValues[modAbs((int)(-sectorIndex), numOfSectors)]);
}

void solve() {
    int numOfSectors, maxProfit = 0;
    long long minSpeed, maxSpeed, speedReduction;
    cin >> numOfSectors;
    int sectorValues[numOfSectors];
    for (int i = 0; i < numOfSectors; ++i) {
        cin >> sectorValues[i];
    }
    cin >> minSpeed >> maxSpeed >> speedReduction;

    long long mod = numOfSectors * speedReduction;
    if (maxSpeed - minSpeed >= mod) {
        for (long long speed = 0; speed < mod; speed += speedReduction) {
            getMaxProfit(speed, speedReduction, maxProfit, sectorValues, numOfSectors);
        }
    }
    else if (maxSpeed % mod < minSpeed % mod) {
        for (long long speed = 0; speed < maxSpeed % mod; speed += speedReduction) {
            getMaxProfit(speed, speedReduction, maxProfit, sectorValues, numOfSectors);
        }
        for (long long speed = minSpeed % mod; speed < mod; speed += speedReduction) {
            getMaxProfit(speed, speedReduction, maxProfit, sectorValues, numOfSectors);
        }
    }
    else {
        for (long long speed = minSpeed % mod; speed <= maxSpeed % mod; speed += speedReduction) {
            getMaxProfit(speed, speedReduction, maxProfit, sectorValues, numOfSectors);
        }
    }
    cout << maxProfit;
}

int main() {
    solve();
    return 0;
}

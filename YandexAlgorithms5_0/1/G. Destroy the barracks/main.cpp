#include <bits/stdc++.h>
using namespace std;

const int MAX_NUM_OF_ROUNDS = 20000;

void barrackOneShot(int& barrackHP, int& enemyCounter, int& soldiersCounter) {
    enemyCounter = max(0, enemyCounter - (soldiersCounter - barrackHP));
    barrackHP = 0;
    soldiersCounter = max(0, soldiersCounter - enemyCounter);
}

void enemyPriority(int& barrackHP, int& enemySpawn, int& enemyCounter, int& soldiersCounter) {
    barrackHP = max(0, barrackHP - max(0, soldiersCounter - enemyCounter));
    enemyCounter = max(0, enemyCounter - soldiersCounter);
    soldiersCounter = max(0, soldiersCounter - enemyCounter);
    enemyCounter += enemySpawn;
}

void barrackDestroyed(int& enemyCounter, int& soldiersCounter) {
    enemyCounter = max(0, enemyCounter - soldiersCounter);
    soldiersCounter = max(0, soldiersCounter - enemyCounter);
}

int oneShotAfterNIteration(int numOfIteration, int barrackHP, int enemySpawn, int enemyCounter, int soldiersCounter) {
    int roundCounter = numOfIteration;
    for (int i = 0; i < numOfIteration; ++i) {
        enemyPriority(barrackHP, enemySpawn, enemyCounter, soldiersCounter);
    }
    if (barrackHP > 0) {
        ++roundCounter;
        barrackOneShot(barrackHP, enemyCounter, soldiersCounter);
    }
    while (enemyCounter > 0) {
        if (soldiersCounter <= 0) {
            return -1;
        }
        ++roundCounter;
        barrackDestroyed(enemyCounter, soldiersCounter);
    }
    return roundCounter;
}

void solve() {
    int soldiersCounter, barrackHP, enemySpawn;
    cin >> soldiersCounter >> barrackHP >> enemySpawn;
    int roundCounter = 0;
    int enemyCounter = 0;
    if (barrackHP >= 2 * soldiersCounter && enemySpawn >= soldiersCounter) {
        cout << -1;
        return;
    }
    while (barrackHP > soldiersCounter) {
        if (soldiersCounter <= 0) {
            cout << -1;
            return;
        }
        ++roundCounter;
        enemyPriority(barrackHP, enemySpawn, enemyCounter, soldiersCounter);
    }
    int minRound = MAX_NUM_OF_ROUNDS;
    for (int i = 0; i < enemyCounter + 1; i++) {
        int numOfRounds = oneShotAfterNIteration(i, barrackHP, enemySpawn, enemyCounter, soldiersCounter);
        if (numOfRounds != -1) {
            minRound = min(minRound, numOfRounds);
        }
    }
    if (minRound >= MAX_NUM_OF_ROUNDS) {
        cout << -1;
        return;
    }
    cout << roundCounter + minRound;
}

int main() {
    solve();
    return 0;
}
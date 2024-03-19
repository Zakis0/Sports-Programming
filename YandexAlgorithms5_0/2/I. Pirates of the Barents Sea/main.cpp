#include <bits/stdc++.h>

using namespace std;

int countNumOfShipsInRow(int sizeOfField, int row, int columnToSkip, vector<vector<bool>> field) {
    int counter = 0;
    for (int j = 0; j < sizeOfField; ++j) {
        if (field[row][j] && j != columnToSkip) {
            ++counter;
        }
    }
    return counter;
}

int getNumOfMoves(int centerMassPos, int sizeOfField, vector<vector<bool>> field) {
    int moveCounter = 0;
    for (int i = 0; i < sizeOfField; ++i) {
        for (int j = 0; j < sizeOfField; ++j) {
            if (field[i][j]) {
                moveCounter += abs(j - centerMassPos);
            }
        }
    }
    int numOfEmptySpaces = 0;
    int leftShips = 0;
    for (int i = 0; i < sizeOfField; ++i) {
        int numOfShipsInRow = countNumOfShipsInRow(sizeOfField, i, (int)centerMassPos, field);
        leftShips += numOfShipsInRow;
        int shipsForFillingEmptySpaces = min(leftShips, numOfEmptySpaces);
        leftShips -= shipsForFillingEmptySpaces;
        numOfEmptySpaces -= shipsForFillingEmptySpaces;
        if (!field[i][(int)centerMassPos]) {
            if (leftShips == 0) {
                ++numOfEmptySpaces;
            }
            else {
                leftShips = max(0, leftShips - 1);
            }
        }
        moveCounter += leftShips + numOfEmptySpaces;
    }
    return moveCounter;
}

void solve() {
    int sizeOfField, i, j;
    cin >> sizeOfField;
    vector<vector<bool>> field(sizeOfField, vector<bool>(sizeOfField));
    for (auto& row : field) {
        fill(row.begin(), row.end(), false);
    }

    float centerMassPos = 0;
    for (int k = 0; k < sizeOfField; ++k) {
        cin >> i >> j;
        centerMassPos += (float)j ;
        field[i - 1][j - 1] = true;
    }
    centerMassPos /= (float)sizeOfField;
    centerMassPos = round(centerMassPos) - 1;

    vector<pair<int, int>> vec;
    vec.reserve(sizeOfField);
    int minMoves = INT32_MAX;
    int epsilon = 5;
    for (int k = -epsilon; k <= epsilon; ++k) {
        minMoves = min(minMoves, getNumOfMoves(max(0, min(sizeOfField - 1, k + (int)centerMassPos)), sizeOfField, field));
    }
    cout << minMoves;
}

int main() {
    solve();
    return 0;
}

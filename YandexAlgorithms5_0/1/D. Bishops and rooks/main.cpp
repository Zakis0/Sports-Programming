#include <bits/stdc++.h>
using namespace std;

const char BISHOP = 'B';
const char ROOK = 'R';
const char EMPTY = '*';

bool pointInField(int i, int j) {
    return i >= 0 && i < 8 && j >= 0 && j < 8;
}

void printAttack(bool attackField[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(attackField[i][j]) {
                cout << "@";
            }
            else {
                cout << "*";
            }
        }
        cout << endl;
    }
}

void printField(char pieceField[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << pieceField[i][j];
        }
        cout << endl;
    }
}

void solve() {
    char piecesField[8][8];
    bool attackField[8][8];

    vector<pair<int, int>> bishopAttack {
            pair(-1, -1),
            pair(1, 1),
            pair(1, -1),
            pair(-1, 1)
    };
    vector<pair<int, int>> rookAttack {
            pair(0, -1),
            pair(0, 1),
            pair(1, 0),
            pair(-1, 0)
    };
    string row;
    for (int i = 0; i < 8; ++i) {
        cin >> row;
        for (int j = 0; j < 8; ++j) {
            piecesField[i][j] = row[j];
            attackField[i][j] = false;
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            vector<pair<int, int>> pieceAttack;
            if (piecesField[i][j] == BISHOP) {
                pieceAttack = bishopAttack;
            }
            else if (piecesField[i][j] == ROOK) {
                pieceAttack = rookAttack;
            }
            else {
                continue;
            }
            attackField[i][j] = true;
            for (int k = 0; k < 4; ++k) {
                int I = i + pieceAttack[k].first;
                int J = j + pieceAttack[k].second;
                while (pointInField(I, J) && piecesField[I][J] == EMPTY) {
                    attackField[I][J] = true;
                    I += pieceAttack[k].first;
                    J += pieceAttack[k].second;
                }
            }
        }
    }
    int counter = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            counter += attackField[i][j] ? 0 : 1;
        }
    }
    cout << counter;
}

int main() {
    solve();
    return 0;
}

#include <bits/stdc++.h>

#define len 51

using namespace std;

const int ALPHABET_LENGTH = 26;

int checkPos(int maxI, int maxJ, char block[][len], char M, char O, int posI, int posJ) {
    int i = 0;

    if (block[posI][posJ]!=M) return 0;
    if(posI - 2 >= 0 && block[posI-1][posJ] == O && block[posI-2][posJ] == O) ++i;
    if(posI + 2 < maxI && block[posI+1][posJ] == O && block[posI+2][posJ] == O) ++i;
    if(posJ - 2 >= 0 && block[posI][posJ-1] == O && block[posI][posJ-2] == O) ++i;
    if(posJ + 2 < maxJ && block[posI][posJ+1] == O && block[posI][posJ+2] == O) ++i;

    if(posI - 2 >= 0 && posJ - 2 >= 0 && block[posI-1][posJ-1] == O && block[posI-2][posJ-2] == O) ++i;
    if(posI - 2 >= 0 && posJ + 2 < maxJ && block[posI-1][posJ+1] == O && block[posI-2][posJ+2] == O) ++i;
    if(posI + 2 < maxI && posJ + 2 < maxJ && block[posI+1][posJ+1] == O && block[posI+2][posJ+2] == O) ++i;
    if(posI + 2 < maxI && posJ - 2 >= 0 && block[posI+1][posJ-1] == O && block[posI+2][posJ-2] == O) ++i;

    return i;
}

int countCurNumOfMOO(int maxI, int maxJ, char block[][len], char M, char O) {
    int numOfMOO = 0;
    for (int i = 0; i < maxI; ++i) {
        for (int j = 0; j < maxJ; ++j) {
            numOfMOO += checkPos(maxI, maxJ, block, M, O, i, j);
        }
    }
    return numOfMOO;
}

int solve(int maxI, int maxJ, char block[][len]) {
    int maxNumOfMOO = 0, curNumOfMOO;
    for(int k = 0; k < ALPHABET_LENGTH; ++k) {
        for(int l = 0; l < ALPHABET_LENGTH; ++l) {
            if (k == l) continue;
            if ('A' + k == 'M' || 'A' + l == 'O') continue;
            curNumOfMOO = countCurNumOfMOO(maxI, maxJ, block, 'A' + k, 'A' + l);
            if (curNumOfMOO > maxNumOfMOO) {
                maxNumOfMOO = curNumOfMOO;
            }
        }
    }
    return maxNumOfMOO;
}

void createBlock(int maxI, int maxJ, char block[][len]) {
    for(int i = 0; i < maxI; ++i) {
        for(int j = 0; j < maxJ; ++j) {
            cin >> block[i][j];
        }
    }
}

int main() {
    int maxI, maxJ;
    cin >> maxI;
    cin >> maxJ;
    char block[len][len];

    createBlock(maxI, maxJ, block);
    cout << solve(maxI, maxJ, block) << endl;
}

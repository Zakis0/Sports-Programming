#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int ALPHABET_LENGTH = 26;

int checkPos(int maxX, int maxY, vector<string> block, char M, char O, int posX, int posY) {
    int i = 0;
    int a = posY - 2 >= 0 && block[posX][posY-1] == O && block[posX][posY-2] == O;
//    cout << a << endl;
    cout << block[posX][posY-1] << endl;
    cout << block[posX][posY-2] << endl;
    if (block[posX][posY]!= M || M == O) return 0;
    if(posX - 2 >= 0 && posY - 2 >= 0 && block[posX-1][posY-1] == O && block[posX-2][posY-2] == O) ++i;
    if(posY - 2 >= 0 && block[posX][posY-1] == O && block[posX][posY-2] == O) ++i;
    if(posX + 2 < maxX && posY - 2 >= 0 && block[posX+1][posY-1] == O && block[posX+2][posY-2] == O) ++i;
    if(posX + 2 < maxX && block[posX+1][posY] == O && block[posX+2][posY] == O) ++i;
    if(posX + 2 < maxX && posY + 2 < maxY && block[posX+1][posY+1] == O && block[posX+2][posY+2] == O) ++i;
    if(posY + 2 < maxY && block[posX][posY+1] == O && block[posX][posY+2] == O) ++i;
    if(posX - 2 >= 0 && posY + 2 < maxY && block[posX-1][posY+1] == O && block[posX-2][posY+2] == O) ++i;
    if(posX - 2 >= 0 && block[posX-1][posY] == O && block[posX-2][posY] == O) ++i;
    return i;
}

int check(int maxX, int maxY, vector<string> block, char M, char O) {
    int cur = 0;
    for (int i = 0; i < maxX; ++i) {
        for (int j = 0; j < maxY; ++j) {
            cur += checkPos(maxX, maxY, block, M, O, i, j);
        }
    }
    return cur;
}

int solve(int maxX, int maxY, vector<string> block) {
    int max = 0, cur;
    for(int k = 0; k < ALPHABET_LENGTH; ++k) {
        for(int l = 0; l < ALPHABET_LENGTH; ++l) {
            cur = check(maxX, maxY, block, ALPHABET[k], ALPHABET[l]);
            if (cur > max) {
                max = cur;
            }
        }
    }
    return max;
}

void createBlock(int maxX, int maxY, vector<string> block) {
    char val;
    for(int i = 0; i < maxX; ++i) {
        for(int j = 0; j < maxY; ++j) {
            cin >> val;
            block[i][j] = val;
        }
    }
}

void printBlock(int maxX, int maxY, vector<string> block) {
    for(int i = 0; i < maxX; ++i) {
        for(int j = 0; j < maxY; ++j) {
            cout << block[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int maxX, maxY;
    cin >> maxY;
    cin >> maxX;

//    string block[maxX];
    vector<string> block;

    createBlock(maxX, maxY, block);
    cout << checkPos(maxX, maxY, block, 'Q', 'M', 5, 3) << endl;
//    cout << solve(maxX, maxY, block) << endl;
}

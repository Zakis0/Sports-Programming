#include <bits/stdc++.h>
using namespace std;

const string REV = "rev";
const string CNT = "cnt";
const int ALPHABET_LENGTH = 26;
const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

vector<int> testVector;
int testCounter = 0;

bool error = false;

int getCharNum(char c) {
    return c - 'a';
}

void incArr(int* arr, int n) {
    for (int i = 0; i < ALPHABET_LENGTH; ++i) {
        arr[i] += n;
    }
}

void incArrN(int* arr, int startPos, int n) {
    for (int i = startPos; i < ALPHABET_LENGTH && i < startPos + n; ++i) {
        ++arr[i];
    }
    for (int i = 0; i < n + startPos - ALPHABET_LENGTH; ++i) {
        ++arr[i];
    }
}

void incArrNRev(int* arr, int startPos, int n) {
    for (int i = startPos; i >= 0 && i > startPos - n; --i) {
        ++arr[i];
    }
    for (int i = ALPHABET_LENGTH - 1; i > ALPHABET_LENGTH - n + startPos; --i) {
        ++arr[i];
    }
}

void printArr(int* arr) {
    cout << ALPHABET[0];
    for (int i = 1; i < ALPHABET_LENGTH; ++i) {
        cout << "\t" << ALPHABET[i];
    }
    cout << endl;
    cout << arr[0];
    for (int i = 1; i < ALPHABET_LENGTH; ++i) {
        cout << "\t" << arr[i];
    }
    cout << endl;
}

int modAbs(int n, int mod) {
    return (n % mod + mod) % mod;
}

void solve() {
    int numOfLettersArray[ALPHABET_LENGTH] = {0};
    int q;
    int numOfPassedLetters;
    int newNumOfLetters, lastNumOfLetters = 0;
    int div, mod;
    int startPos, endPos = 0;
    bool rev = false;
    string commandType;
    char commandLetter;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        cin >> commandType;
        cin >> numOfPassedLetters;

        newNumOfLetters = numOfPassedLetters - lastNumOfLetters;

        div = newNumOfLetters / ALPHABET_LENGTH;
        mod = newNumOfLetters % ALPHABET_LENGTH;

        if (div != 0) {
            incArr(numOfLettersArray, div);
        }
        startPos = endPos;
        if (!rev) {
            incArrN(numOfLettersArray, startPos, mod);
            endPos = modAbs(startPos + mod, ALPHABET_LENGTH);
        }
        else {
            incArrNRev(numOfLettersArray, startPos, mod);
            endPos = modAbs(startPos - mod, ALPHABET_LENGTH);
        }
        if (commandType == REV) {
            rev = !rev;
            if (mod == 0) {
                endPos += rev ? -3 : 3;
            }
            else {
                endPos += rev ? -2 : 2;
            }
            //cout << "_____" << endl;
        }
        if (commandType == CNT) {
            cin >> commandLetter;
            int charPos = getCharNum(commandLetter);
            cout << numOfLettersArray[charPos] << endl;
            testVector.emplace_back(numOfLettersArray[charPos]);
        }
        lastNumOfLetters = numOfPassedLetters;
        printArr(numOfLettersArray);
    }
}

void solveTest() {
    int n;
    cin >> n;

    string mode = "ABC";

    long long int index, indLast = 0;

    char ch, letter = 0;

    int mult = 1;

    int counts[26];
    long long int  cycles = 0;
    for (int i = 0; i < 26; i++){
        counts[i] = 0;
    }

    for (int j = 0; j < n; j++){
        cin >> mode[0] >> mode[1] >> mode[2];
        cin >> index;

        int test = index;

        if (mode == "cnt") {
            cin >> ch;
        }

        index -= indLast;
        indLast = index + indLast;
        cycles += index / 26;
        index = index % 26;

        for (int i = 0; i < index; i++){
            counts[(26 + i * mult + letter) % 26] += 1;
        }
        letter = (26 + index * mult + letter) % 26;
        if(mode == "cnt"){
            cout << cycles + counts[ch - 'a'] << endl;
            if (testVector[testCounter++] != cycles + counts[ch - 'a']) {
                cout << "Error " << mode << " " << test << " " << ch << " | " << testVector[testCounter - 1] << " " << cycles + counts[ch - 'a'] << endl;
                error = true;
                return;
            }
        } else {
            mult *= -1;
            letter = (2 * mult + letter) % 26;
        }
//        if (mode == "rev") {
//            cout << "_____" << endl;
//        }
    }
}

void startTest() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(20);
    freopen("input.txt", "r", stdin);
    solveTest();
}

void startMe() {
    freopen("input.txt", "r", stdin);
    solve();
}

int getRand(int start, int end) {
    return start + rand() % end;
}

void generateTest(int N) {
    ofstream file("input.txt", ios_base::out);
    int counter = 0;
    int MAX_STEP = 1000;
    int step;
    string mode;

    bool canBeZero = true;
    if (file.is_open()) {
        file << N << endl;
        for (int i = 0; i < N; ++i) {
            if (getRand(1, 2) == 1) mode = REV; else mode = CNT;
            file << mode << " ";

            step = getRand(canBeZero ? 0 : 1, MAX_STEP);
            counter += step;
            file << counter;

            if (mode == CNT) {
                file << " " << ALPHABET[getRand(0, 25)] << endl;
            }
            else {
                file << endl;
            }

            if (i == 0) {
                canBeZero = false;
            }
        }
        file.close();
    }
}

void createTest(char letter, int number) {
    ofstream file("input.txt", ios_base::out);
    if (file.is_open()) {
        file << 2 << endl;
        file << REV << " " << 0 << endl;
        file << CNT << " " << number << " " << letter << endl;
        file.close();
    }
}

void downgradeTest() {
    int startNumber = 371;
    char letter;
    for (int number = startNumber; number > 0; --number) {
        letter = 'z';
        while (letter >= 'a') {
            error = false;
            createTest(letter, number);
            startMe();
            startTest();
            if (error) {
                cout << number << " " << letter << endl;
            }
            letter -= 1;
        }
    }
}

int main() {
    bool start = false;

    if (start) {
        srand(time(0));
        int numOfTest = 100000;
        int N = 2;
        for (int i = 0; i < numOfTest; ++i) {
            generateTest(N);
            startMe();
            startTest();
        }
    }
    else {
        startMe();
        startTest();
    }
//    downgradeTest();
    return 0;
}
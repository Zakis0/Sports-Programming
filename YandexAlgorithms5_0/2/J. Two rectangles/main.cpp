#include <bits/stdc++.h>

#include <utility>

//#define DEBUG
//#define PRINT_TIME
//#define READ_FROM_FILE

#ifdef READ_FROM_FILE
#define cin fin
#endif

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

using ll [[maybe_unused]] = long long;
using ld [[maybe_unused]] = double;

using namespace std;

const string NO = "NO";
const string YES = "YES";

const char EMPTY_CHAR = '.';
const char SHADED_CHAR = '#';

const char A_CHAR = 'a';
const char B_CHAR = 'b';

const string EMPTY = "EMPTY";
const string SHADED = "SHADED";
const string FIGURE_A = "FIGURE_A";
const string FIGURE_B = "FIGURE_B";

struct CellState {
    string state;
    explicit CellState() {
        this->state = EMPTY;
    }
    explicit CellState(string state) {
        this->state = std::move(state);
    }
    bool isShaded() const {
        return state == SHADED;
    }
    bool isEmpty() const {
        return state == EMPTY;
    }
    bool isFigureA() const {
        return state == FIGURE_A;
    }
    bool isFigureB() const {
        return state == FIGURE_B;
    }
    bool isFigure() const {
        return state == FIGURE_A || state == FIGURE_B;
    }
};

void printField(vector<vector<CellState>>& field) {
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            if (field[i][j].isShaded()) {
                cout << SHADED_CHAR;
            }
            else if (field[i][j].isEmpty()) {
                cout << EMPTY_CHAR;
            }
            else if (field[i][j].isFigureA()) {
                cout << A_CHAR;
            }
            else if (field[i][j].isFigureB()) {
                cout << B_CHAR;
            }
        }
        cout << endl;
    }
}

pair<int, int> findTopLeft(vector<vector<CellState>>& field) {
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            if (field[i][j].isShaded()) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

void horizontalReflectField(vector<vector<CellState>>& field) {
    vector<CellState> temp;
    for (int i = 0; i < field.size() / 2; ++i) {
        temp = field[field.size() - 1 - i];
        field[field.size() - 1 - i] = field[i];
        field[i] = temp;
    }
}
void verticalReflectField(vector<vector<CellState>>& field) {
    CellState temp;
    for (int j = 0; j < field[0].size() / 2; ++j) {
        for (int i = 0; i < field.size(); ++i) {
            temp = field[i][field[0].size() - 1 - j];
            field[i][field[0].size() - 1 - j] = field[i][j];
            field[i][j] = temp;
        }
    }
}

void resetField(vector<vector<CellState>>& field) {
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            if (field[i][j].isFigure()) {
                field[i][j].state = SHADED;
            }
        }
    }
}

struct TestResult {
    bool success;
    int top, left, maxVerticalLength, maxHorizontalLength;
    TestResult() {
        this->success = false;
        this->top = -1;
        this->left = -1;
        this->maxVerticalLength = -1;
        this->maxHorizontalLength = -1;
    }
    TestResult(int top, int left) {
        this->success = false;
        this->top = top;
        this->left = left;
        this->maxVerticalLength = -1;
        this->maxHorizontalLength = -1;
    }
    TestResult(int top, int left, int maxVerticalLength, int maxHorizontalLength) {
        this->success = true;
        this->top = top;
        this->left = left;
        this->maxVerticalLength = maxVerticalLength;
        this->maxHorizontalLength = maxHorizontalLength;
    }
    friend ostream& operator<<(ostream &os, const TestResult &test){
        if (!test.success) return os << "Result: False" << ";"
           " top: " << test.top << ";"
           " left: " << test.left << ";";

        return os << "Result: True" << ";"
          " top: " << test.top << ";"
          " left: " << test.left << ";"
          " verticalLength: " << test.maxVerticalLength << ";"
          " horizontalLength: " << test.maxHorizontalLength << ";";
    }
};

TestResult testField(vector<vector<CellState>>& field, pair<int, int> topLeft) {
    int maxHorizontalLength = 0;
    for (int i = topLeft.first; i < field.size(); ++i) {
        int curHorizontalLength = 0;
        for (int j = topLeft.second; j < field[0].size(); ++j) {
            if (!field[i][j].isShaded()) {
                break;
            }
            else {
                ++curHorizontalLength;
            }
            if (i == topLeft.first) {
                ++maxHorizontalLength;
            }
        }
        if (!field[i][topLeft.first].isShaded() && i != topLeft.first) {
            break;
        }
        if (curHorizontalLength < maxHorizontalLength) {
            return {topLeft.first, topLeft.second};
        }
    }
    int maxVerticalLength = 0;
    for (int j = topLeft.second; j < topLeft.second + maxHorizontalLength; ++j) {
        int curVerticalLength = 0;
        for (int i = topLeft.first; i < field.size(); ++i) {
            if (!field[i][j].isShaded()) {
                break;
            }
            else {
                ++curVerticalLength;
            }
            if (j == topLeft.second) {
                ++maxVerticalLength;
            }
        }
        if (curVerticalLength < maxVerticalLength) {
            return {topLeft.first, topLeft.second};
        }
    }
    return {topLeft.first, topLeft.second, maxVerticalLength, maxHorizontalLength};
}

void fillFigure(vector<vector<CellState>>& field, const string& figureType, int top, int left, int maxVerticalLength, int maxHorizontalLength) {
    for (int i = top; i < top + maxVerticalLength; ++i) {
        for (int j = left; j < left + maxHorizontalLength; ++j) {
            field[i][j].state = figureType;
        }
    }
}

bool hasDidntCountedParts(vector<vector<CellState>>& field) {
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            if (field[i][j].isShaded()) {
                return true;
            }
        }
    }
    return false;
}

int fillRow(vector<vector<CellState>>& field, const string& figureType, int top, int left, int maxHorizontalLength) {
    int numOfReplacement = 0;
    for (int j = left; j < left + maxHorizontalLength; ++j) {
        ++numOfReplacement;
        field[top][j].state = figureType;
    }
    return numOfReplacement;
}
int fillColumn(vector<vector<CellState>>& field, const string& figureType, int top, int left, int maxVerticalLength) {
    int numOfReplacement = 0;
    for (int i = top; i < top + maxVerticalLength; ++i) {
        ++numOfReplacement;
        field[i][left].state = figureType;
    }
    return numOfReplacement;
}
void fillOneRowOrColumn(vector<vector<CellState>>& field, int numOfShaded, int top, int left, int maxVerticalLength, int maxHorizontalLength) {
    int numOfReplacement = fillRow(field, FIGURE_B, top, left, maxHorizontalLength);
    if (numOfReplacement == numOfShaded) {
        fillRow(field, FIGURE_A, top, left, maxHorizontalLength);
        fillColumn(field, FIGURE_B, top, left, maxVerticalLength);
    }
}

void printResult(vector<vector<CellState>>& field) {
    cout << YES << endl;
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[0].size(); ++j) {
            if (field[i][j].isFigureA()) {
                cout << A_CHAR;
            }
            else if (field[i][j].isFigureB()) {
                cout << B_CHAR;
            }
            else {
                cout << EMPTY_CHAR;
            }
        }
        cout << endl;
    }
}

const string E = "EMPTY_COMMAND";
const string H = "HORIZONTAL";
const string V = "VERTICAL";
const string HV = "HORIZONTAL_VERTICAL";
const string VH = "VERTICAL_HORIZONTAL";

void applyCommand(const string& command, vector<vector<CellState>>& field) {
    if (command == H) {
        horizontalReflectField(field);
    }
    else if (command == V) {
        verticalReflectField(field);
    }
    else if (command == HV) {
        horizontalReflectField(field);
        verticalReflectField(field);
    }
    else if (command == VH) {
        verticalReflectField(field);
        horizontalReflectField(field);
    }
}

string getReverseCommand(const string& command) {
    if (command == H) return H;
    if (command == V) return V;
    if (command == HV) return VH;
    if (command == VH) return HV;
    return E;
}

void solve(ifstream& fin) {
    int m, n;
    cin >> m >> n;
    vector<vector<CellState>> field(m, vector<CellState>(n));

    int numOfShaded = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;
            if (c == SHADED_CHAR) {
                ++numOfShaded;
                field[i][j].state = SHADED;
            }
            else {
                field[i][j].state = EMPTY;
            }
        }
    }

//    applyCommand(V, field);
//    printField(field);
//    return;

    if (numOfShaded <= 1) {
        cout << NO;
        return;
    }

    vector<string> commands = {E, H, V, HV, VH};

    for (const string& command: commands) {
        applyCommand(command, field);
#ifdef DEBUG
        cout << "Field before test 1 with command " << command << endl;
        printField(field); cout << endl;
#endif
        pair<int, int> topLeft = findTopLeft(field);
        TestResult testResult = testField(field, topLeft);
        if (testResult.success) {
            fillFigure(field, FIGURE_A, testResult.top, testResult.left, testResult.maxVerticalLength,
                       testResult.maxHorizontalLength);
#ifdef DEBUG
            cout << "Field after test 1" << endl;
            printField(field); cout << endl;
#endif
            if (!hasDidntCountedParts(field)) {
                fillOneRowOrColumn(field, numOfShaded, testResult.top, testResult.left, testResult.maxVerticalLength,
                                   testResult.maxHorizontalLength);
                applyCommand(getReverseCommand(command), field);
                printResult(field);
                return;
            }
            topLeft = findTopLeft(field);
            testResult = testField(field, topLeft);
            if (testResult.success) {
                fillFigure(field, FIGURE_B, testResult.top, testResult.left, testResult.maxVerticalLength,
                           testResult.maxHorizontalLength);
                if (!hasDidntCountedParts(field)) {
                    applyCommand(getReverseCommand(command), field);
                    printResult(field);
                    return;
                }
            }
        }
        resetField(field);
        applyCommand(getReverseCommand(command), field);
#ifdef DEBUG
        cout << "Field after reset" << endl;
        printField(field); cout << endl;
#endif
    }
    cout << NO;
}

int main() {
    // Time measure
    time_t start, end;
    time(&start);
    // Read from file
    ifstream fin("input.txt");
    // Float precision
    cout << setprecision(20);

    // Starting solution
    solve(fin);

    time(&end);
#ifdef PRINT_TIME
    cout << endl << "The time: " << difftime(end, start) << " seconds" << endl;
#endif
    return 0;
}

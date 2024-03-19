#include <bits/stdc++.h>

//#define cin fin

using namespace std;

struct MyMax {
    int i, j, value;
    MyMax() {
        this->i = -1;
        this->j = -1;
        this->value = -1;
    }
    MyMax(int i, int j, int value) {
        this->i = i;
        this->j = j;
        this->value = value;
    }
    bool operator>(MyMax const& myMax) const {
        return value > myMax.value;
    }
    bool operator<(MyMax const& myMax) const {
        return myMax > *this;
    }
};

struct Line {
    int index, firstMax, secondMax, firstMaxI, firstMaxJ;
    Line() {
        this->index = -1;
        this->firstMax = -1;
        this->secondMax =-1;
        this->firstMaxI =-1;
        this->firstMaxJ =-1;
    }
    Line(int index, int firstMax, int secondMax, int firstMaxI, int firstMaxJ) {
        this->index = index;
        this->firstMax = firstMax;
        this->secondMax = secondMax;
        this->firstMaxI = firstMaxI;
        this->firstMaxJ = firstMaxJ;
    }
    friend ostream& operator<<(ostream &os, const Line &line){
        return os <<
        line.index<< " " <<
        line.firstMax << " " <<
        line.secondMax << " " <<
        line.firstMaxI << " " <<
        line.firstMaxJ;
    }
};

pair<MyMax, MyMax> getTwoMax(vector<int>& values, int lineIndex, bool isColumn) {
    int firstMaxPos = -1;
    int secondMaxPos = -1;
    for (int i = 0; i < values.size(); ++i) {
        if (values[i] >= values[firstMaxPos]) {
            secondMaxPos = firstMaxPos;
            firstMaxPos = i;
        }
        else if (values[i] >= values[secondMaxPos]) {
            secondMaxPos = i;
        }
    }
    int firstMax = firstMaxPos != -1 ? values[firstMaxPos] : -1;
    int secondMax = secondMaxPos != -1 ? values[secondMaxPos] : -1;
    if (isColumn) {
        return {MyMax(firstMaxPos, lineIndex, firstMax), MyMax(secondMaxPos, lineIndex, secondMax)};
    }
    return {MyMax(lineIndex, firstMaxPos, firstMax), MyMax(lineIndex, secondMaxPos, secondMax)};
}

vector<int> getColumnVector(vector<vector<int>>& field, int columnIndex) {
    vector<int> column;
    column.reserve(field.size());
    for (auto& row : field) {
        column.emplace_back(row[columnIndex]);
    }
    return column;
}

int getMax(vector<vector<int>>& field, int rowToSkip = -1, int columnToSkip = -1) {
    int globalMax = -1;
    for (int i = 0; i < field.size(); ++i) {
        if (i == rowToSkip) {
            continue;
        }
        for (int j = 0; j < field[0].size(); ++j) {
            if (j == columnToSkip) {
                continue;
            }
            globalMax = max(field[i][j], globalMax);
        }
    }
    return globalMax;
}

void solve() {
    int numOfRaces, numOfClasses;

    ifstream fin("input.txt");

    cin >> numOfRaces >> numOfClasses;

    vector<Line> maxInRow;
    vector<Line> maxInColumn;

    vector<vector<int>> field(numOfRaces, vector<int>(numOfClasses));

    MyMax globalMax;

    for (int i = 0; i < numOfRaces; ++i) {
        for (int j = 0; j < numOfClasses; ++j) {
            cin >> field[i][j];
            if (field[i][j] > globalMax.value) {
                globalMax.value = field[i][j];
                globalMax.i = i;
                globalMax.j = j;
            }
        }
    }
    for (int i = 0; i < numOfRaces; ++i) {
        pair<MyMax, MyMax> twoMaxes = getTwoMax(field[i], i, false);
        maxInRow.emplace_back(i, twoMaxes.first.value, twoMaxes.second.value, twoMaxes.first.i, twoMaxes.first.j);
    }
    for (int j = 0; j < numOfClasses; ++j) {
        vector<int> column = getColumnVector(field, j);
        pair<MyMax, MyMax> twoMaxes = getTwoMax(column, j, true);
        maxInColumn.emplace_back(j, twoMaxes.first.value, twoMaxes.second.value, twoMaxes.first.i, twoMaxes.first.j);
    }
    Line maxRow, maxColumn;
    int maxValueInRow = -1;
    for (int i = 0; i < numOfRaces; ++i) {
        if (maxInRow[i].firstMaxJ == globalMax.j) {
            if (maxInRow[i].secondMax > maxValueInRow) {
                maxValueInRow = maxInRow[i].secondMax;
                maxRow = maxInRow[i];
            }
        }
        else {
            if (maxInRow[i].firstMax > maxValueInRow) {
                maxValueInRow = maxInRow[i].firstMax;
                maxRow = maxInRow[i];
            }
        }
    }
    int maxValueInColumn = -1;
    for (int j = 0; j < numOfClasses; ++j) {
        if (maxInColumn[j].firstMaxI == globalMax.i) {
            if (maxInColumn[j].secondMax > maxValueInColumn) {
                maxValueInColumn = maxInColumn[j].secondMax;
                maxColumn = maxInColumn[j];
            }
        }
        else {
            if (maxInColumn[j].firstMax > maxValueInColumn) {
                maxValueInColumn = maxInColumn[j].firstMax;
                maxColumn = maxInColumn[j];
            }
        }
    }
    int maxWhenBanMaxRow = getMax(field, maxRow.index, globalMax.j);
    int maxWhenBanMaxColumn = getMax(field, globalMax.i, maxColumn.index);
    if (maxWhenBanMaxRow < maxWhenBanMaxColumn) {
        cout << maxRow.index + 1 << " " << globalMax.j + 1;
    }
    else {
        cout << globalMax.i + 1 << " " << maxColumn.index + 1;
    }
}

int main() {
    solve();
    return 0;
}

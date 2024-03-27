#define DEBUG
#define LOCAL_RUN
//#define PRINT_TIME

//#define INPUT_FROM_FILE
//#define OUTPUT_TO_FILE


#ifdef LOCAL_RUN
#define INPUT_FILE_NAME "../input.txt"
#define OUTPUT_FILE_NAME "../output.txt"
#else
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"
#endif

#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()

using ll [[maybe_unused]] = long long;
using ld [[maybe_unused]] = double;

using namespace std;

bool checkIfPointsPairExist(
        pair<int, int> point1,
        pair<int, int> point2,
        set<pair<int, int>>& points,
        set<pair<int, int>>& pointsToInsert,
        int& minPointsToInsert,
        bool& breakFlag
        ) {
    int numOfNeededPoints = 2;
    set<pair<int, int>> curPointsToInsert;
    if (points.contains(point1)) {
        --numOfNeededPoints;
    }
    else {
        curPointsToInsert.insert(point1);
    }
    if (points.contains(point2)) {
        --numOfNeededPoints;
    }
    else {
        curPointsToInsert.insert(point2);
    }
    if (numOfNeededPoints < minPointsToInsert) {
        minPointsToInsert = numOfNeededPoints;
        pointsToInsert = curPointsToInsert;
        if (numOfNeededPoints == 0) {
            breakFlag = true;
        }
    }
    return breakFlag;
}

bool checkIfPointsExist(
        pair<int, int> point1,
        pair<int, int> point2,
        set<pair<int, int>>& points,
        set<pair<int, int>>& pointsToInsert,
        int& minPointsToInsert,
        bool& breakFlag
        ) {
    bool exitProgram;
    if (point1.first == point2.first) {
        int distance = abs(point1.second - point2.second);
        exitProgram = checkIfPointsPairExist(
                pair(point1.first + distance, point1.second),
                pair(point1.first + distance, point2.second),
                points, pointsToInsert, minPointsToInsert, breakFlag);
        exitProgram = exitProgram || checkIfPointsPairExist(
                pair(point1.first - distance, point1.second),
                pair(point1.first - distance, point2.second),
                points, pointsToInsert, minPointsToInsert, breakFlag);
    }
    else if (point1.second == point2.second) { // seems that it`s already in else branch
        int distance = abs(point1.first - point2.first);
        exitProgram = checkIfPointsPairExist(
                pair(point1.first, point1.second + distance),
                pair(point2.first, point2.second + distance),
                points, pointsToInsert, minPointsToInsert, breakFlag);
        exitProgram = exitProgram || checkIfPointsPairExist(
                pair(point1.first, point1.second - distance),
                pair(point2.first, point2.second - distance),
                points, pointsToInsert, minPointsToInsert, breakFlag);
    }
    else {
        int deltaX = point1.first - point2.first;
        int deltaY = point1.second - point2.second;
        float slope = (float)deltaY / deltaX;
        deltaX = abs(deltaX);
        deltaY = abs(deltaY);
        if (slope < 0) {
            exitProgram = checkIfPointsPairExist(
                    pair(point1.first + deltaY, point1.second + deltaX),
                    pair(point2.first + deltaY, point2.second + deltaX),
                    points, pointsToInsert, minPointsToInsert, breakFlag);
            exitProgram = exitProgram || checkIfPointsPairExist(
                    pair(point1.first - deltaY, point1.second - deltaX),
                    pair(point2.first - deltaY, point2.second - deltaX),
                    points, pointsToInsert, minPointsToInsert, breakFlag);
        }
        else {
            exitProgram = checkIfPointsPairExist(
                    pair(point1.first - deltaY, point1.second + deltaX),
                    pair(point2.first - deltaY, point2.second + deltaX),
                    points, pointsToInsert, minPointsToInsert, breakFlag);
            exitProgram = exitProgram || checkIfPointsPairExist(
                    pair(point1.first + deltaY, point1.second - deltaX),
                    pair(point2.first + deltaY, point2.second - deltaX),
                    points, pointsToInsert, minPointsToInsert, breakFlag);
        }
    }
    return exitProgram;
}

void solve() {
    int n, x, y;
    set<pair<int, int>> points1, points2;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        points1.insert(pair(x, y));
        points2.insert(pair(x, y));
    }
    set<pair<int, int>> pointsToInsert;
    int minPointsToInsert = 4;
    bool breakFlag = false;

    for (pair<int, int> point1: points1) {
        points2.erase(point1);
        for (pair<int, int> point2: points2) {
            if(checkIfPointsExist(point1, point2, points1, pointsToInsert, minPointsToInsert, breakFlag)) {
                break;
            }
        }
        if (breakFlag) {
            break;
        }
    }
    cout << minPointsToInsert << endl;
    for (pair<int, int> pointToInsert: pointsToInsert) {
        cout << pointToInsert.first << " " << pointToInsert.second << endl;
    }
}

int main() {
    // File input/output
#ifdef INPUT_FROM_FILE
    freopen(INPUT_FILE_NAME, "r", stdin);
#endif
#ifdef OUTPUT_TO_FILE
    // Save the current stdout file descriptor
    int stdout_fd = dup(fileno(stdout));
    // Redirect stdout to a file
    freopen(OUTPUT_FILE_NAME, "w", stdout);
#endif
    // Float/Double precision
    std::cout << setprecision(20);

    // Time measure
    std::time_t start = clock();

    // Start solution
    solve();

    std::time_t end = clock();
#ifdef OUTPUT_TO_FILE
    // Flush stdout to ensure all output is written before redirection
    fflush(stdout);
    // Restore stdout back to the original file descriptor
    dup2(stdout_fd, fileno(stdout));
    // Close the duplicated file descriptor
    close(stdout_fd);
#endif
    std::cout << setprecision(5);
#ifdef PRINT_TIME
    std::cout << "_____________________________" << endl <<
    "The time: " << (ld)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
#endif
    return 0;
}

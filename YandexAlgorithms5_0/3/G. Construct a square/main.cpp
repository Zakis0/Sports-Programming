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

void solve() {
    int n, x, y;
    set<pair<int, int>> points;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        points.insert(pair(x, y));
    }
    vector<pair<int, int>> leftTopOffset = { pair(-1, 0), pair(0, -1), pair(-1, -1)};
    vector<pair<int, int>> leftBottomOffset = { pair(-1, 0), pair(0, 1), pair(-1, 1)};
    vector<pair<int, int>> rightTopOffset = { pair(1, 0), pair(0, -1), pair(1, -1)};
    vector<pair<int, int>> rightBottomOffset = { pair(1, 0), pair(0, 1), pair(1, 1)};

    vector<vector<pair<int, int>>> offsets = {leftTopOffset, leftBottomOffset, rightTopOffset, rightBottomOffset};

    int minPointsToInsert = 4;
    set<pair<int, int>> pointsToInsert;
    for (pair<int, int> point: points) {
        for (const vector<pair<int, int>>& offset: offsets) {
            int curMinPointsToInsert = 3;
            for (pair<int, int> offsetPair: offset) {
                if (points.contains(pair(point.first + offsetPair.first, point.second + offsetPair.second))) {
                    --curMinPointsToInsert;
                }
            }
            if (curMinPointsToInsert < minPointsToInsert) {
                minPointsToInsert = curMinPointsToInsert;
                pointsToInsert.clear();
                for (pair<int, int> offsetPair: offset) {
                    if (!points.contains(pair(point.first + offsetPair.first, point.second + offsetPair.second))) {
                        pointsToInsert.insert(pair(point.first + offsetPair.first, point.second + offsetPair.second));
                    }
                }
            }
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

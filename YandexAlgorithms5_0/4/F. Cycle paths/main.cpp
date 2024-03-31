//#define DEBUG
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
    int width, height, numOfCrackedTiles, x, y;
    cin >> width >> height >> numOfCrackedTiles;
    vector<pair<int, int>> crackedTiles(numOfCrackedTiles);
    vector<int> heights(numOfCrackedTiles);
    for (int i = 0; i < numOfCrackedTiles; ++i) {
        cin >> crackedTiles[i].first >> crackedTiles[i].second;
    }
    sort(all(crackedTiles));
    for (int i = 0; i < numOfCrackedTiles; ++i) {
        heights[i] = crackedTiles[i].second;
    }
    vector<int> leftPartMinHeight = heights;
    vector<int> leftPartMaxHeight = heights;
    vector<int> rightPartMinHeight = heights;
    vector<int> rightPartMaxHeight = heights;

    for (int i = 0; i < numOfCrackedTiles - 1; ++i) {
        leftPartMinHeight[i + 1] = min(leftPartMinHeight[i], leftPartMinHeight[i + 1]);
        leftPartMaxHeight[i + 1] = max(leftPartMaxHeight[i], leftPartMaxHeight[i + 1]);
    }
    for (int i = numOfCrackedTiles - 1; i > 0; --i) {
        rightPartMinHeight[i - 1] = min(rightPartMinHeight[i], rightPartMinHeight[i - 1]);
        rightPartMaxHeight[i - 1] = max(rightPartMaxHeight[i], rightPartMaxHeight[i - 1]);
    }

    int left = 1, right = min(width, height);
    while (left <= right) {
        int center = (left + right) / 2;
        int leftPointIndex = 0;
        bool changeLeft = true;
        for (int rightPointIndex = 0; rightPointIndex < numOfCrackedTiles; ++rightPointIndex) {
            while (crackedTiles[rightPointIndex].first -
                crackedTiles[leftPointIndex++].first >= center);
            int maxHeight = max(--leftPointIndex > 0 ? leftPartMaxHeight[leftPointIndex - 1] : -1,
                                rightPointIndex + 1 < numOfCrackedTiles ?
                                rightPartMaxHeight[rightPointIndex + 1] : -1);
            int minHeight = min(leftPointIndex > 0 ? leftPartMinHeight[leftPointIndex - 1] : INT32_MAX,
                                rightPointIndex + 1 < numOfCrackedTiles ?
                                rightPartMinHeight[rightPointIndex + 1] : INT32_MAX);
            if (maxHeight - minHeight + 1 <= center) {
                right = center - 1;
                changeLeft = false;
                break;
            }
        }
        if (changeLeft) {
            left = center + 1;
        }
    }
    cout << left;
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
    std::cout << std::endl << "_____________________________" << endl <<
    "The time: " << (ld)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
#endif
    return 0;
}

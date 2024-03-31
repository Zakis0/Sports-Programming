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

const char CAN_BUILD_CHAR = '#';
const char CANNOT_BUILD_CHAR = '.';

#define MAX_NUM_OP_POINTS 2000

int pointsForBuild[MAX_NUM_OP_POINTS][MAX_NUM_OP_POINTS];

void getMapOfMaxBlockSizeThatCanBeBuildInPoint() {
    for (int i = MAX_NUM_OP_POINTS - 2; i >= 0; --i) {
        for (int j = MAX_NUM_OP_POINTS - 2; j >= 0; --j) {
            if (!pointsForBuild[i][j]) {
                continue;
            }
            pointsForBuild[i][j] = 1 + min(pointsForBuild[i + 1][j],
                                           min(pointsForBuild[i][j + 1],
                                               pointsForBuild[i + 1][j + 1]));
        }
    }
}

bool existsPlus(int blockSize) {
#ifdef DEBUG
    cout << blockSize << endl;
#endif
    for (int i = 0; i < MAX_NUM_OP_POINTS; ++i) {
        for (int j = 0; j < MAX_NUM_OP_POINTS; ++j) {
            if (pointsForBuild[i][j] >= blockSize &&
                i + blockSize < MAX_NUM_OP_POINTS &&
                j + blockSize < MAX_NUM_OP_POINTS &&
                i - blockSize >= 0 &&
                j - blockSize >= 0 &&
                pointsForBuild[i + blockSize][j] >= blockSize &&
                pointsForBuild[i - blockSize][j] >= blockSize &&
                pointsForBuild[i][j + blockSize] >= blockSize &&
                pointsForBuild[i][j - blockSize] >= blockSize) {
                return true;
            }
        }
    }
    return false;
}

void solve() {
    char c;
    int height, width;
    std::time_t start = clock();
    cin >> height >> width;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cin >> c;
            pointsForBuild[i][j] = c == CAN_BUILD_CHAR;
        }
    }
    getMapOfMaxBlockSizeThatCanBeBuildInPoint();
    float blockSize = 0.5;
    while (existsPlus((int)(blockSize *= 2)));
    int left = (int)blockSize / 2, right = (int)blockSize;
    while (left <= right) {
        int center = left + (right - left) / 2;
        bool existsPlusForBlockSize = existsPlus(center);
        if (existsPlusForBlockSize && !existsPlus(center + 1)) {
            cout << center;
        }
        if (existsPlusForBlockSize) left = center + 1;
        else right = center - 1;
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
    std::cout << std::endl << "_____________________________" << endl <<
    "The time: " << (ld)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
#endif
    return 0;
}

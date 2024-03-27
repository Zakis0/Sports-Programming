#define DEBUG
#define LOCAL_RUN
#define PRINT_TIME

#define INPUT_FROM_FILE
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

bool canBuildBlock(pair<int, int> topLeftCornerCoords,
                   int blockSize,
                   set<pair<int, int>>& pointsForBuild) {
    for (int i = 0; i < blockSize; ++i) {
        for (int j = 0; j < blockSize; ++j) {
            if (!pointsForBuild.contains(pair(
                    topLeftCornerCoords.first + j,
                    topLeftCornerCoords.second + i))) {
                return false;
            }
        }
    }
    return true;
}

bool canBuildPlus(pair<int, int> middleBlockTopLeftCornerCoords,
                  int blockSize,
                  map<int, set<pair<int, int>>>& topLeftCornersOfExistedBlockWithSize) {
    return topLeftCornersOfExistedBlockWithSize[blockSize].contains(middleBlockTopLeftCornerCoords) && // middle
            topLeftCornersOfExistedBlockWithSize[blockSize].contains(// top
    pair(middleBlockTopLeftCornerCoords.first,
         middleBlockTopLeftCornerCoords.second - blockSize)) &&
            topLeftCornersOfExistedBlockWithSize[blockSize].contains(// bottom
    pair(middleBlockTopLeftCornerCoords.first,
         middleBlockTopLeftCornerCoords.second + blockSize)) &&
            topLeftCornersOfExistedBlockWithSize[blockSize].contains(// left
    pair(middleBlockTopLeftCornerCoords.first - blockSize,
         middleBlockTopLeftCornerCoords.second)) &&
            topLeftCornersOfExistedBlockWithSize[blockSize].contains(// right
    pair(middleBlockTopLeftCornerCoords.first + blockSize,
         middleBlockTopLeftCornerCoords.second));
}

map<int, set<pair<int, int>>> getMapOfExistedBlockBySize(set<pair<int, int>>& pointsForBuild) {

}

bool existsPlus(int blockSize, set<pair<int, int>>& pointsForBuild) {
#ifdef DEBUG
    cout << blockSize << endl;
#endif
    set<pair<int, int>> topLeftCornersOfExistedBlock;
    for (pair<int, int> blockTopLeftCornerCoords: pointsForBuild) {
        if (canBuildBlock(blockTopLeftCornerCoords, blockSize, pointsForBuild)) {
            topLeftCornersOfExistedBlock.insert(blockTopLeftCornerCoords);
        }
    }
    for (pair<int, int> middleBlockTopLeftCornerCoords: pointsForBuild) {
        if (canBuildPlus(middleBlockTopLeftCornerCoords, blockSize, topLeftCornersOfExistedBlock)) {
            return true;
        }
    }
    return false;
}

void solve() {
    char c;
    int height, width;
    cin >> height >> width;
    set<pair<int, int>> pointsForBuild;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cin >> c;
            if (c == CAN_BUILD_CHAR) {
                pointsForBuild.insert(pair(i, j));
            }
        }
    }
    float blockSize = 0.5;
    while (existsPlus((int)(blockSize *= 2), pointsForBuild));
    int left = (int)blockSize / 2, right = (int)blockSize;
    while (left <= right) {
        int center = left + (right - left) / 2;
        bool existsPlusForBlockSize = existsPlus(center, pointsForBuild);
        if (existsPlusForBlockSize && !existsPlus(center + 1, pointsForBuild)) {
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

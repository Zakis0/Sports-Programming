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

int getHeightByWidth(int width, vector<int>& words) {
    bool firstInLine = true;
    int height = 1;
    int leftLineWidth = width;
    for (int word: words) {
        if (word > width) {
            return INT32_MAX;
        }
        if (word + !firstInLine > leftLineWidth) {
            ++height;
            firstInLine = true;
            leftLineWidth = width;
        }
        leftLineWidth -= word + !firstInLine;
        firstInLine = false;
    }
    return height;
}

int getHeightDiffWithWidth(int broder, int width, vector<int>& firstPart, vector<int>& secondPart) {
    return getHeightByWidth(width - broder, secondPart) - getHeightByWidth(broder, firstPart);
}
int getMaxHeightByWidth(int broder, int width, vector<int>& firstPart, vector<int>& secondPart) {
    return max(getHeightByWidth(broder, firstPart), getHeightByWidth(width - broder, secondPart));
}

void solve() {
    int width, n, m, wordLength, maxWordsLengthFirstPart = 0, maxWordsLengthSecondPart = 0;
    cin >> width >> n >> m;
    vector<int> firstPart, secondPart;
    for (int i = 0; i < n; ++i) {
        cin >> wordLength;
        maxWordsLengthFirstPart = max(wordLength, maxWordsLengthFirstPart);
        firstPart.emplace_back(wordLength);
    }
    for (int i = 0; i < m; ++i) {
        cin >> wordLength;
        maxWordsLengthSecondPart = max(wordLength, maxWordsLengthSecondPart);
        secondPart.emplace_back(wordLength);
    }
#ifdef DEBUG
    cout << "____________" << endl;
    for (int i = maxWordsLengthFirstPart; i <= width - maxWordsLengthSecondPart; ++i) {
        cout << i << " ";
        cout << max(getHeightByWidth(i, firstPart),
                    getHeightByWidth(width - i, secondPart)) << endl;
    }
    cout << "____________" << endl;
    for (int i = maxWordsLengthFirstPart; i <= width - maxWordsLengthSecondPart; ++i) {
        cout << i << " ";
        cout << getHeightDiffWithWidth(i, width, firstPart, secondPart) << endl;
    }
    cout << "____________" << endl;
#endif
    int left = maxWordsLengthFirstPart, right = width - maxWordsLengthSecondPart;
    while (left <= right) {
        int center = left + (right - left) / 2;
        int centerHeightDiff = getHeightDiffWithWidth(center, width, firstPart, secondPart);
        if (centerHeightDiff == 0) {
            cout << getMaxHeightByWidth(center, width, firstPart, secondPart);
            return;
        }
        if (centerHeightDiff < 0) left = center + 1;
        else right = center - 1;
    }
    cout << min(getMaxHeightByWidth(left, width, firstPart, secondPart),
                getMaxHeightByWidth(left - 1, width, firstPart, secondPart));
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

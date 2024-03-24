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
    int n, number;
    cin >> n;
    map<int, int> counter;
    set<int> numbersSet;
    pair<int, int> bestPair(-1, -1);
    for (int i = 0; i < n; ++i) {
        cin >> number;
        numbersSet.insert(number);
        ++counter[number];
    }
    if (numbersSet.size() == 1) {
        cout << 0;
        return;
    }
    vector<int> numbersVector(all(numbersSet));
    for (int i = 0; i < numbersVector.size() - 1; ++i) {
        if (abs(numbersVector[i] - numbersVector[i + 1]) == 1 &&
                counter[numbersVector[i]] + counter[numbersVector[i + 1]] >
                counter[bestPair.first] + counter[bestPair.second]) {
            bestPair.first = numbersVector[i];
            bestPair.second = numbersVector[i + 1];
        }
    }
    if (bestPair.first == -1) {
        cout << n - 1;
    }
    else {
        cout << (n - counter[bestPair.first] - counter[bestPair.second]);
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

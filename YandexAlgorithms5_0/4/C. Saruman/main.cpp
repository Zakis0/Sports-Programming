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
    int n, m, numOfRegiments;
    ll numOfTroops;
    cin >> n >> m;
    vector<int> regiments;
    vector<ll> numOfTroopsBefore = {0};
    for (int i = 0; i < n; ++i) {
        cin >> numOfTroops;
        regiments.emplace_back(numOfTroops);
        numOfTroopsBefore.emplace_back(regiments[i]);
        numOfTroopsBefore[i + 1] += numOfTroopsBefore[i];
    }
    for (int i = 0; i < m; ++i) {
        bool continueFlag = false;
        cin >> numOfRegiments >> numOfTroops;
        int left = numOfRegiments, right = n;
        while (left <= right) {
            int center = left + (right - left) / 2;
            if (numOfTroopsBefore[center] - numOfTroopsBefore[center - numOfRegiments] == numOfTroops) {
                cout << center - numOfRegiments + 1 << endl;
                continueFlag = true;
                break;
            }
            if (numOfTroopsBefore[center] - numOfTroopsBefore[center - numOfRegiments] < numOfTroops) left = center + 1;
            else right = center - 1;
        }
        if (continueFlag) {
            continue;
        }
        cout << -1 << endl;
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

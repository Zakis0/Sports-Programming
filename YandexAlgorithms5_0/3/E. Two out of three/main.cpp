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
    int n, value;
    set<int> set1, set2, set3;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        set1.insert(value);
    }
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        set2.insert(value);
    }
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        set3.insert(value);
    }
    set<int> intersection12, intersection23, intersection13, result;
    set_intersection(all(set1), all(set2),inserter(intersection12, intersection12.begin()));
    set_intersection(all(set2), all(set3),inserter(intersection23, intersection23.begin()));
    set_intersection(all(set1), all(set3),inserter(intersection13, intersection13.begin()));

    set_union(all(intersection12), all(intersection23),inserter(result, result.begin()));
    set_union(all(result), all(intersection13), inserter(result, result.begin()));

    for (int number: result) {
        cout << number << " ";
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

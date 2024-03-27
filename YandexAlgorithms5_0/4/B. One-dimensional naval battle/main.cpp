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

//ll computeNumOfSpaces(ll k) {
//    ll result = -1;
//    for (int i = 0; i < k; ++i) {
//        result += (k - i) * (i + 1 + 1);
//    }
//    return result;
//}

// Holes
// (k(1 + k) / 2) - 1
// Ships
// 1(k - 0) + 2(k - 1) + 3(k - 2) + 4(k - 3) + ... + (k - 1) * (k - (k - 2)) + k(k - (k - 1))

// k + 2k + 3k + 4k + ... + k * k = k * ((1 + k) / 2 * k) = (k * k * (k+1)) / 2

// 0 - 2 - 6 - 12 + ... + k(k - 1)       Sum of Triangular number
// -2(1 + 3 + 6 + ... + k(k - 1)/2) = -2 * ((k * k * k - k) / 6) = -(k * k * k - k) / 3

// (k * k * (k+1)) / 2 - (k * k * k - k) / 3 = k * k * k / 2 + k * k / 2 - k * k * k / 3 + k / 3 =
// = k * k * k / 6 + k * k / 2 + k / 3

// k / 2 + k * k / 2 - 1 + k * k * k / 6 + k * k / 2 + k / 3 =
// = k * k * k / 6 + k * k + k * 5/6 - 1 = (k * k * k + 5 * k) / 6 + k * k - 1
ll computeNumOfSpaces(ll k) {
    return (k * k * k + 5 * k) / 6 + k * k - 1;
}

void solve() {
    ll n, numOfSpaces;
    cin >> n;
    ld k = 0.5;
    // Looking for k, when numOfSpaces > n and numOfSpaces do not overflow
    while ((numOfSpaces = computeNumOfSpaces((ll)(k *= 2))) <= n && numOfSpaces > 0);
    int left = (int)k / 2, right = (int)k;
    while (left <= right) {
        int center = left + (right - left) / 2;
        if (computeNumOfSpaces(center) <= n && computeNumOfSpaces(center + 1) > n) cout << center;
        if (computeNumOfSpaces(center) < n) left = center + 1;
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

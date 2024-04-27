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

class RandomizedSet {
    map<int, int> m;
    vector<int> keys;
public:
    RandomizedSet() {}
    bool insert(int val) {
        if (m.contains(val)) return false;
        m[val] = keys.size();
        keys.emplace_back(val);
        return true;
    }
    bool remove(int val) {
        if (!m.contains(val)) return false;
        keys[m[val]] = keys.back();
        keys.pop_back();
        m[keys[m[val]]] = m[val];
        m.erase(val);
        return true;
    }
    int getRandom() {
        return keys[rand() % m.size()];
    }
};

void solve() {
    RandomizedSet* obj = new RandomizedSet();
    cout << obj->insert(0) << endl;
    cout << obj->insert(1) << endl;
    cout << obj->remove(0) << endl;
    cout << obj->insert(2) << endl;
    cout << obj->remove(1) << endl;
    cout << obj->getRandom() << endl;
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
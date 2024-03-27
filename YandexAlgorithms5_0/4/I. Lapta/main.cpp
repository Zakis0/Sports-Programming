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

struct Player {
    int x, y, speed;
    Player(int x, int y, int speed) {
        this->x = x;
        this->y = y;
        this->speed = speed;
    }
    [[nodiscard]] ld distanceTo(pair<int, int> point) const {
        return sqrt(pow(point.first - x, 2) + pow(point.second - y, 2));
    }
    [[nodiscard]] ld timeToPoint(pair<int, int> point) const {
        return distanceTo(point) / speed;
    }
};

void solve() {
    int maxStrikeRange, numOfEnemies, x, y, speed;
    cin >> maxStrikeRange >> numOfEnemies;
    vector<Player> players;
    for (int i = 0; i < numOfEnemies; ++i) {
        cin >> x >> y >> speed;
        players.emplace_back(x, y, speed);
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
//#define DEBUG
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

struct Match {
    int x1, y1, x2, y2;
    pair<int, int> matchVector;
    Match(int x1, int y1, int x2, int y2) {
        if (x1 > x2 || (x1 == x2 && y1 <= y2)) {
            this->x1 = x2;
            this->y1 = y2;
            this->x2 = x1;
            this->y2 = y1;
        }
        else {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
        }
        matchVector = pair(x2 - x1, y2 - y1);
        if (matchVector.second < 0) {
            matchVector.first *= -1;
            matchVector.second *= -1;
        }
        if (matchVector.second == 0) {
            matchVector.first = abs(matchVector.first);
        }
    }
    pair<int, int> getDistance(const Match& match) const {
        float match1CenterX = (float)(max(x1, x2) + min(x1, x2)) / 2;
        float match1CenterY = (float)(max(y1, y2) + min(y1, y2)) / 2;
        float match2CenterX = (float)(max(match.x1, match.x2) + min(match.x1, match.x2)) / 2;
        float match2CenterY = (float)(max(match.y1, match.y2) + min(match.y1, match.y2)) / 2;
        return pair(
                (int)(match2CenterX - match1CenterX),
                (int)(match2CenterY - match1CenterY)
        );
    }
    bool operator <(const Match& match) const {
        if (x1 == match.x1) {
            if (y1 == match.y1) {
                if (x2 == match.x2) {
                    return y2 < match.y2;
                }
                return x2 < match.x2;
            }
            return y1 < match.y1;
        }
        return x1 < match.x1;
    }
    bool operator >(const Match& match) const {
        return match < *this;
    }
};

void solve() {
    int n, x1, y1, x2, y2;
    cin >> n;

    set<Match> aImage, bImage;
    map<pair<int, int>, vector<Match>> aVectorToMatch, bVectorToMatch;
    for (int i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        Match match(x1, y1, x2, y2);
        aImage.insert(match);
        aVectorToMatch[match.matchVector].emplace_back(match);
    }
    for (int i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        Match match(x1, y1, x2, y2);
        bImage.insert(match);
        bVectorToMatch[match.matchVector].emplace_back(match);
    }

    set<Match> matchesToErase;
    for (Match match: aImage) {
        if (bVectorToMatch[match.matchVector].empty()) {
            matchesToErase.insert(match);
        }
    }
    set<Match> difference;
    set_difference(all(aImage), all(matchesToErase),
                        inserter(difference, difference.begin()));
    aImage = difference;

    matchesToErase.clear();
    difference.clear();
    for (Match match: bImage) {
        if (aVectorToMatch[match.matchVector].empty()) {
            matchesToErase.insert(match);
        }
    }

    set_difference(all(bImage), all(matchesToErase),
                   inserter(difference, difference.begin()));
    bImage = difference;

    map<pair<int, int>, int> offsetsCounters;
    for (Match aMatch: aImage) {
        for (Match& bMatchForVector: bVectorToMatch[aMatch.matchVector]) {
            pair<int, int> distance = bMatchForVector.getDistance(aMatch);
            ++offsetsCounters[distance];
        }
    }
    int maxOffsetCounter = 0;
    for (pair<pair<int, int>, int> offsetCounter: offsetsCounters) {
        maxOffsetCounter = max(offsetCounter.second, maxOffsetCounter);
    }
    cout << n - maxOffsetCounter;
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

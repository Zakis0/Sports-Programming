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

ld distance(ld x1, ld y1, ld x2, ld y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

struct Player {
    int x, y, speed;
    Player(int x, int y, int speed) {
        this->x = x;
        this->y = y;
        this->speed = speed;
    }
    bool operator ==(Player& player) {
        return x == player.x && y == player.y && speed == player.speed;
    }
    [[nodiscard]] ld distanceTo(int x, int y) const {
        return distance(this->x, this->y, x, y);
    }
};

const int MAX_TIME = 4000;
const ld EPSILON = 0.0001;


set<pair<ld, ld>> findCircleIntersections(ld x1, ld y1, ld r1, ld x2, ld y2, ld r2) {
    set<pair<ld, ld>> intersections;
    ld d = distance(x1, y1, x2, y2);
    if (d > r1 + r2 || d < fabs(r1 - r2)) {
        return intersections;
    }
    ld a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
    ld h = sqrt(r1 * r1 - a * a);

    ld x2_prime = x1 + a * (x2 - x1) / d;
    ld y2_prime = y1 + a * (y2 - y1) / d;

    ld x3 = x2_prime + h * (y2 - y1) / d;
    ld y3 = y2_prime - h * (x2 - x1) / d;

    ld x4 = x2_prime - h * (y2 - y1) / d;
    ld y4 = y2_prime + h * (x2 - x1) / d;

    intersections.insert(make_pair(x3, y3));
    intersections.insert(make_pair(x4, y4));
    return intersections;
}

pair<ld, ld> checkTime(ld time, vector<Player>& players, int maxStrikeRange) {
    set<pair<ld, ld>> intersections;
    for (int i = 0; i < players.size(); ++i) {
        for (int j = i + 1; j < players.size(); ++j) {
            for (pair<ld, ld> point:
                findCircleIntersections(players[i].x, players[i].y, players[i].speed * time,
                                    players[j].x, players[j].y, players[j].speed * time)) {
                if (point.second >= 0 &&
                        distance(0, 0, point.first, point.second) <= maxStrikeRange) {
                    intersections.insert(point);
                }
            }
        }
    }
    bool doNotAddTopPoint0D = false;
    for (Player& player: players) {
        doNotAddTopPoint0D = doNotAddTopPoint0D || distance(0, maxStrikeRange, player.x, player.y) <= player.speed * time;
        for (pair<ld, ld> point:
                findCircleIntersections(0, 0, maxStrikeRange,
                                        player.x, player.y, player.speed * time)) {
            if (point.second >= 0) {
                intersections.insert(point);
            }
        }
    }
    if (!doNotAddTopPoint0D) {
        intersections.insert(pair(0, maxStrikeRange));
    }
    set<pair<ld, ld>> pointsToRemove;
    for (pair<ld, ld> point: intersections) {
        for (Player player: players) {
            double dist = distance(point.first, point.second, player.x, player.y);
            double runRange = player.speed * time;
            if (distance(point.first, point.second, player.x, player.y) < player.speed * time &&
                    abs(dist - runRange) > EPSILON) {
                pointsToRemove.insert(point);
            }
        }
    }
    set<pair<ld, ld>> difference;
    set_difference(all(intersections), all(pointsToRemove),
                        inserter(difference, difference.begin()));
    if (difference.empty()) {
        return {-1.0, -1.0};
    }
    auto minElement = max_element(all(difference), [](pair<ld, ld> point1, pair<ld, ld> point2) {
        return distance(point1.first, point1.second, 0, 0) <
                distance(point2.first, point2.second, 0, 0);
    });
    return {minElement->first, minElement->second};
}

void solve() {
//    findCircleIntersections(0, 0, 5,-1, 1, 2.929);
    int maxStrikeRange, numOfEnemies, x, y, speed;
    cin >> maxStrikeRange >> numOfEnemies;
    vector<Player> players;
    for (int i = 0; i < numOfEnemies; ++i) {
        cin >> x >> y >> speed;
        players.emplace_back(x, y, speed);
    }
    ld left = 0, right = MAX_TIME;
    pair<ld, ld> point, lastGoodPoint;
    while (right - left > 2 * EPSILON) {
        ld center = (left + right) / 2;
        point = checkTime(center, players, maxStrikeRange);
        if (point != pair(-1.0, -1.0)) {
            left = center;
            lastGoodPoint = point;
        }
        else right = center;
    }
    cout << left << endl;
    cout << lastGoodPoint.first << " " << lastGoodPoint.second;
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
    // Float/ld precision
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

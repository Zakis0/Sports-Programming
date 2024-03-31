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

ld initDownVolume(const vector<pair<int, int>>& vertexes,
                  const vector<int>& up,
                  const vector<int>& down,
                  int index, ld H) {
    int downIndex = down[index];
    int leftUp = upper_bound(all(up), downIndex) - up.begin() - 1;
    int rightUp = leftUp + 1;
    int l = vertexes[rightUp].first - vertexes[leftUp].first;
    return l * H;
}

ld areaOfTrap(int y1,
              int y2,
              ld H,
              int l){
    return (2 * H + y1 + y2) / 2 * l;
}

ld realDownVolume(const vector<pair<int, int>>& vertexes,
                  const vector<int>& up,
                  const vector<int>& down,
                  int index, ld H) {
    int downIndex = down[index];
    int leftUp = upper_bound(all(up), downIndex) - up.begin() - 1;
    int rightUp = leftUp + 1;
    ld ans = 0;
    for (int i = leftUp; i < rightUp; i++){
        ans += areaOfTrap(vertexes[i].second,
                          vertexes[i + 1].second, H,
                          vertexes[i].first - vertexes[i+1].first);
    }
    return ans;
}

ld calcWaterLevel(int y1, int y2, ld H, int l){

}

void solve() {
    int n;
    ld height;
    cin >> n >> height;
    vector<pair<int, int>> points(n + 1 + 2);
    vector<int> peakIndexes(100);
    vector<pair<int, int>> peakIndexesForlowland(100);
    vector<int> lowlandIndexes(100);
    vector<ld> volumeDown(100);
    vector<ld> realVolumeDown(100);
    //vector<ld> waterLevel();

    cin >> points[1].first >> points[1].second;
    points[0].first = points[1].first;
    points[0].second = INT32_MAX;
    int lastPeak = 0;
    lowlandIndexes.emplace_back(0);
    for (int i = 2; i < n + 1; ++i) {
        cin >> points[i].first >> points[i].second;
        if((points[i - 1] < points[i - 2]) && (points[i - 1] < points[i])) {
            peakIndexesForlowland.emplace_back(lastPeak, -1);
            lowlandIndexes.emplace_back(i - 1);
        }
        if((points[i - 1] > points[i - 2]) && (points[i - 1] > points[i])) {
            if (peakIndexesForlowland[peakIndexesForlowland.size() - 1].second == -1){
                peakIndexesForlowland[peakIndexesForlowland.size() - 1].second = lastPeak;
            }
            lastPeak = i - 1;
            peakIndexes.emplace_back(i - 1);
        }
    }
    points[n + 2] = pair(points[n + 1].first, INT32_MAX);
    lowlandIndexes.emplace_back(n + 2);

    for(int i = 0; i < lowlandIndexes.size(); i++){
        realVolumeDown[i] = realDownVolume(points,
                                           peakIndexes,
                                           lowlandIndexes,i,
                                           0);
        volumeDown[i] = initDownVolume(points,
                                       peakIndexes,
                                       lowlandIndexes,
                                       i, height);
    }
    ld sp = 0;
    bool flag = true;
    while(flag){
        for(int i = lowlandIndexes.size(); i >= 0; i--){
            pair<int, int> abroad = peakIndexesForlowland[i];
            volumeDown[i] += sp;
            if(volumeDown[i] > realVolumeDown[i] && abroad.first < abroad.second){
                sp = volumeDown[i] - realVolumeDown[i];
                volumeDown[i] -= sp;
            }
        }
        for(int i = 0; i < lowlandIndexes.size(); i++){
            pair<int, int> abroad = peakIndexesForlowland[i];
            pair<int, int> lastAbroad = peakIndexesForlowland[i - 1];
            volumeDown[i] += sp;
            if(abroad.first > abroad.second){
                if(i != 0) if(volumeDown[i-1] == realVolumeDown[i-1] && lastAbroad.second < abroad.second){
                    sp = volumeDown[i] - realVolumeDown[i];
                    volumeDown[i] -= sp;
                }
                if(volumeDown[i] > realVolumeDown[i]){
                    sp = volumeDown[i] - realVolumeDown[i];
                    volumeDown[i] -= sp;
                }
            }
        }

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

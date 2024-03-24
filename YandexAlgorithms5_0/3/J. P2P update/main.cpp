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

class Device {
    static int numOfDevices;

    int deviceIndex;

    map<int, int> devicesValues;
    set<int> downloadedUpdateParts;
    set<int> notDownloadedUpdateParts;

    vector<pair<Device*, int>> requests;

public:
    explicit Device(int numOfUpdateParts, bool firstDevice = false) {
        deviceIndex = numOfDevices++;
        if (firstDevice) {
            for (int i = 0; i < numOfUpdateParts; ++i) {
                downloadedUpdateParts.insert(i);
            }
        }
    }
    bool haveDownloadedAllUpdateParts() const {
        return notDownloadedUpdateParts.empty();
    }
    int getNumOfDownloadedUpdateParts() const {
        return downloadedUpdateParts.size();
    }
    void downloadPartFromDevice(int partIndex, const Device* device) {
        ++devicesValues[device->deviceIndex];
        notDownloadedUpdateParts.erase(partIndex);
        downloadedUpdateParts.insert(partIndex);
    }
    int determineRarestPart(vector<Device*>& network) const {
        map<int, int> counterOfNumberOfDownloadedParts;
        for (Device* device: network) {
            set<int> intersectionOfNotDownloadedUpdateParts;
            set_intersection(all(notDownloadedUpdateParts),
                             all(device->notDownloadedUpdateParts),
                             inserter(intersectionOfNotDownloadedUpdateParts,
                                      intersectionOfNotDownloadedUpdateParts.begin()));
            for (int updatePartIndex: intersectionOfNotDownloadedUpdateParts) {
                ++counterOfNumberOfDownloadedParts[updatePartIndex];
            }
        }
        int rarestPart = -1;
        int howManyDevicesAreMissingUpdatePart = 0;
        for (pair<int, int> partCounter: counterOfNumberOfDownloadedParts) {
            if (partCounter.second > howManyDevicesAreMissingUpdatePart) {
                rarestPart = partCounter.first;
                howManyDevicesAreMissingUpdatePart = partCounter.second;
            }
        }
        return rarestPart;
    }
    void requestRarestPart(vector<Device*>& network, int rarestPartIndex) {
        vector<Device*> devicesWithUpdatePart = getVectorOfDevicesWithUpdatePart(network, rarestPartIndex);
        Device* deviceToRequest = min_element(all(devicesWithUpdatePart), [](Device* device1, Device* device2) {
            if (device1->getNumOfDownloadedUpdateParts() == device2->getNumOfDownloadedUpdateParts()) {
                return device1->deviceIndex < device2->deviceIndex;
            }
            return device1->getNumOfDownloadedUpdateParts() < device2->getNumOfDownloadedUpdateParts();
        })[0];
        deviceToRequest->requests.emplace_back(this, rarestPartIndex);
    }
    static vector<Device*> getVectorOfDevicesWithUpdatePart(vector<Device*>& network, int rarestPartIndex) {
        vector<Device*> devicesWithUpdatePart;
        for (Device* device: network) {
            if (device->downloadedUpdateParts.contains(rarestPartIndex)) {
                devicesWithUpdatePart.emplace_back(device);
            }
        }
        return devicesWithUpdatePart;
    }
    void processRequest() {
        
    }
};

int Device::numOfDevices = 0;

void solve() {
    int numOfDevices, numOfUpdateParts;
    cin >> numOfDevices >> numOfUpdateParts;
    int numOfDoneDevices = 1;

    vector<Device*> network;

    network.push_back(new Device(numOfUpdateParts, true));
    for (int i = 1; i < numOfDevices; ++i) {
        network.emplace_back(new Device(numOfUpdateParts));
    }
    while (numOfDoneDevices != numOfDevices) {

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

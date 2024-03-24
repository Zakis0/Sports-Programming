#define DEBUG
//#define LOCAL_RUN
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
    int usedTimeSlots;
    int indexOfDeviceThatShareUpdatePartInLastRound;

    map<int, int> devicesValues;
    set<int> downloadedUpdateParts;
    set<int> notDownloadedUpdateParts;

    vector<pair<Device*, int>> requests;

public:
    explicit Device(int numOfUpdateParts, bool firstDevice = false) {
        usedTimeSlots = 0;
        indexOfDeviceThatShareUpdatePartInLastRound = -1;
        deviceIndex = numOfDevices++;
        if (firstDevice) {
            for (int i = 0; i < numOfUpdateParts; ++i) {
                downloadedUpdateParts.insert(i);
            }
        }
        else {
            for (int i = 0; i < numOfUpdateParts; ++i) {
                notDownloadedUpdateParts.insert(i);
            }
        }
    }
    [[nodiscard]] bool haveDownloadedAllUpdateParts() const {
        return notDownloadedUpdateParts.empty();
    }
    [[nodiscard]] unsigned long getNumOfDownloadedUpdateParts() const {
        return downloadedUpdateParts.size();
    }
    [[nodiscard]] int getIndex() const {
        return deviceIndex;
    }
    void increaseUsedTimeSlots() {
        ++usedTimeSlots;
    }
    [[nodiscard]] int getUsedTimeSlots() const {
        return usedTimeSlots;
    }
    void increaseValueOfDeviceThatShareUpdatePartInLastRound() {
        if (indexOfDeviceThatShareUpdatePartInLastRound != -1) {
            ++devicesValues[indexOfDeviceThatShareUpdatePartInLastRound];
        }
    }
    void resetIndexOfDeviceThatShareUpdatePartInLastRound() {
        indexOfDeviceThatShareUpdatePartInLastRound = -1;
    }
    void downloadPartFromDevice(int partIndex, const Device* device,
            map<int, vector<Device*>>& devicesWithUpdatePart,
            map<int, int>& downloadedUpdatePartCounters) {
        indexOfDeviceThatShareUpdatePartInLastRound = device->deviceIndex;
        notDownloadedUpdateParts.erase(partIndex);
        downloadedUpdateParts.insert(partIndex);
        devicesWithUpdatePart[partIndex].emplace_back(this);
        ++downloadedUpdatePartCounters[partIndex];
    }
    int determineRarestPartIndex(map<int, int>& downloadedUpdatePartCounters) const {
        int rarestPart = min_element(all(downloadedUpdatePartCounters), [this](
                pair<int, int> updatePartCounter1, pair<int, int> updatePartCounter2
                ) {
            if (notDownloadedUpdateParts.contains(updatePartCounter1.first) &&
                !notDownloadedUpdateParts.contains(updatePartCounter2.first)) {
                return true;
            }
            if (!notDownloadedUpdateParts.contains(updatePartCounter1.first) &&
                notDownloadedUpdateParts.contains(updatePartCounter2.first)) {
                return false;
            }
            if (updatePartCounter1.second == updatePartCounter2.second) {
                return updatePartCounter1.first < updatePartCounter2.first;
            }
            return updatePartCounter1.second < updatePartCounter2.second;
        })->first;
        return rarestPart;
    }
    void requestRarestPart(int rarestPartIndex, map<int, vector<Device*>>& devicesWithUpdatePart) {
        Device* deviceToRequest = min_element(all(devicesWithUpdatePart[rarestPartIndex]), [](Device* device1, Device* device2) {
            if (device1->getNumOfDownloadedUpdateParts() == device2->getNumOfDownloadedUpdateParts()) {
                return device1->deviceIndex < device2->deviceIndex;
            }
            return device1->getNumOfDownloadedUpdateParts() < device2->getNumOfDownloadedUpdateParts();
        })[0];
        deviceToRequest->requests.emplace_back(this, rarestPartIndex);
    }
    void processRequest(
            map<int, vector<Device*>>& devicesWithUpdatePart,
            map<int, int>& downloadedUpdatePartCounters) {
        if (requests.empty()) {
            return;
        }
        pair<Device*, int> requestToProcess = min_element(all(requests), [this](pair<Device*, int> request1, pair<Device*, int> request2) {
            if (devicesValues[request1.first->deviceIndex] == devicesValues[request2.first->deviceIndex]) {
                if (request1.first->getNumOfDownloadedUpdateParts() == request2.first->getNumOfDownloadedUpdateParts()) {
                    return request1.first->deviceIndex < request2.first->deviceIndex;
                }
                return request1.first->getNumOfDownloadedUpdateParts() < request2.first->getNumOfDownloadedUpdateParts();
            }
            return devicesValues[request1.first->deviceIndex] > devicesValues[request2.first->deviceIndex];
        })[0];
        requestToProcess.first->downloadPartFromDevice(
                requestToProcess.second,
                this,
                devicesWithUpdatePart,
                downloadedUpdatePartCounters);
    }
    void clearRequests() {
        requests.clear();
    }
};

int Device::numOfDevices = 0;

void clearRequests(vector<Device*>& network) {
    for (Device* device: network) {
        device->clearRequests();
    }
}
void resetIndexesOfDeviceThatShareUpdatePartInLastRound(vector<Device*>& undoneDevices) {
    for (Device* device: undoneDevices) {
        device->resetIndexOfDeviceThatShareUpdatePartInLastRound();
    }
}

void clearDoneDevices(vector<Device*>& undoneDevices) {
    undoneDevices.erase(remove_if(all(undoneDevices), [](Device* device) {
        return device->haveDownloadedAllUpdateParts();
    }), undoneDevices.end());
}

void increaseTimeSlotCounter(vector<Device*>& undoneDevices) {
    for (Device* device: undoneDevices) {
        device->increaseUsedTimeSlots();
    }
}

void solve() {
    int numOfDevices, numOfUpdateParts;
    cin >> numOfDevices >> numOfUpdateParts;

    vector<Device*> network;
    vector<Device*> undoneDevices;

    network.push_back(new Device(numOfUpdateParts, true));
    for (int i = 1; i < numOfDevices; ++i) {
        network.emplace_back(new Device(numOfUpdateParts));
        undoneDevices.emplace_back(network[network.size() - 1]);
    }
    map<int, vector<Device*>> devicesWithUpdatePart;
    map<int, int> downloadedUpdatePartCounters;
    for (int i = 0; i < numOfUpdateParts; ++i) {
        devicesWithUpdatePart[i].emplace_back(network[0]);
        ++downloadedUpdatePartCounters[i];
    }
    while (!undoneDevices.empty()) {
        for (Device* device: undoneDevices) {
            int rarestPartIndex = device->determineRarestPartIndex(downloadedUpdatePartCounters);
            device->requestRarestPart(rarestPartIndex, devicesWithUpdatePart);
        }
        for (Device* device: network) {
            device->processRequest(devicesWithUpdatePart, downloadedUpdatePartCounters);
        }
        for (Device* device: undoneDevices) {
            device->increaseValueOfDeviceThatShareUpdatePartInLastRound();
        }
        increaseTimeSlotCounter(undoneDevices);
        resetIndexesOfDeviceThatShareUpdatePartInLastRound(undoneDevices);
        clearDoneDevices(undoneDevices);
        clearRequests(network);
    }
    for (Device* device: network) {
        if (device->getIndex() == 0) {
            continue;
        }
        cout << device->getUsedTimeSlots() << " ";
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
    std::cout << std:: endl << "_____________________________" << endl <<
    "The time: " << (ld)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
#endif
    return 0;
}

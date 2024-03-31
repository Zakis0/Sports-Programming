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

struct Party {
    int numOfVotes, bribe, index;
    Party(int initNumOfVotes, int bribe, int index) {
        this->numOfVotes = initNumOfVotes;
        this->bribe = bribe;
        this->index = index;
    }
    bool operator<(const Party& party) const {
        return numOfVotes < party.numOfVotes;
    }
    bool operator>(const Party& party) const {
        return party < *this;
    }
};

void sortByIndex(vector<Party>& parties) {
    sort(parties.begin(), parties.end(), [](Party party1, Party party2) {
        return party1.index < party2.index;
    });
}

void solve() {
    int numOfPoliticalParties, initNumOfVotes, bribe;
    cin >> numOfPoliticalParties;
    vector<Party> parties;
    for (int i = 0; i < numOfPoliticalParties; ++i) {
        cin >> initNumOfVotes >> bribe;
        parties.emplace_back(initNumOfVotes, bribe, i);
    }
    sort(all(parties), greater<>());

    ll totalVotes = 0;
    vector<int> sumOfExtraVotesPrevParties;
    for (int i = 0; i < numOfPoliticalParties; ++i) {
        ll checkOverflowSum = totalVotes - i * (ll)parties[i].numOfVotes;
        totalVotes = totalVotes + (ll)parties[i].numOfVotes;
        sumOfExtraVotesPrevParties.emplace_back((checkOverflowSum > 1000000000) ? 1000000000 : checkOverflowSum);
    }
    vector<int> neededVotes;
    neededVotes.emplace_back(parties[0].numOfVotes +
                             (numOfPoliticalParties > 1 &&
                              parties[0].numOfVotes == parties[1].numOfVotes));

    for (int i = 1; i < numOfPoliticalParties; ++i) {
        int left = 0, right = i;
        while (left + 1 < right) {
            int center = (left + right) / 2;
            if (sumOfExtraVotesPrevParties[center] + parties[i].numOfVotes <=
                parties[center].numOfVotes)  {
                left = center;
            }
            else right = center;
        }
        int iPartiesNumOfVotesAfterAddingExtraVotes = parties[i].numOfVotes + sumOfExtraVotesPrevParties[left];
        int difference = parties[left].numOfVotes - iPartiesNumOfVotesAfterAddingExtraVotes;
        int numOfPartiesBefore = left + 1;
        int div = difference / (numOfPartiesBefore + 1);
        int mod = difference % (numOfPartiesBefore + 1);
        iPartiesNumOfVotesAfterAddingExtraVotes += div * numOfPartiesBefore + min(mod + 1, numOfPartiesBefore);
        neededVotes.emplace_back(iPartiesNumOfVotesAfterAddingExtraVotes);
    }
    int minSum = INT32_MAX, indexOfPartyForBribe;
    for (int i = 0; i < numOfPoliticalParties; i++) {
        if ((parties[i].bribe != -1) && (neededVotes[i] - parties[i].numOfVotes + parties[i].bribe < minSum)) {
            minSum = neededVotes[i] - parties[i].numOfVotes + parties[i].bribe;
            indexOfPartyForBribe = i;
        }
    }
    if (indexOfPartyForBribe == 0) {
        cout << minSum << endl << parties[indexOfPartyForBribe].index + 1 << endl;
        if (neededVotes[0] > parties[0].numOfVotes) {
            ++parties[0].numOfVotes;
            --parties[1].numOfVotes;
        }
        sortByIndex(parties);
        for (int i = 0; i < numOfPoliticalParties; ++i) {
            cout << parties[i].numOfVotes << " ";
        }
        return;
    }
    int left = 0, right = indexOfPartyForBribe;
    while (left + 1 < right) {
        int center = (left + right) / 2;
        if (sumOfExtraVotesPrevParties[center] + parties[indexOfPartyForBribe].numOfVotes <=
            parties[center].numOfVotes)  {
            left = center;
        }
        else right = center;
    }
    int bestPartiesNumOfVotesAfterAddingExtraVotes = parties[indexOfPartyForBribe].numOfVotes + sumOfExtraVotesPrevParties[left];
    int difference = parties[left].numOfVotes - bestPartiesNumOfVotesAfterAddingExtraVotes;
    int numOfPartiesBefore = left + 1;
    int div = difference / (numOfPartiesBefore + 1);
    int mod = difference % (numOfPartiesBefore + 1);
    mod = min(mod + 1, numOfPartiesBefore);
    bestPartiesNumOfVotesAfterAddingExtraVotes += div * numOfPartiesBefore + mod;

    cout << minSum << endl << parties[indexOfPartyForBribe].index + 1 << endl;
    for (int i = 0; i <= left; ++i) {
        parties[i].numOfVotes = parties[left].numOfVotes - div;
    }
    for (int i = 0; i < mod; ++i) {
        --parties[i].numOfVotes;
    }
    parties[indexOfPartyForBribe].numOfVotes = bestPartiesNumOfVotesAfterAddingExtraVotes;
    sortByIndex(parties);
    for (int i = 0; i < numOfPoliticalParties; ++i) {
        cout << parties[i].numOfVotes << " ";
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

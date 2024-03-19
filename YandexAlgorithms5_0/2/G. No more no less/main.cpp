#include <bits/stdc++.h>

using namespace std;

void solve() {
    int numOfArrays, arrayLength, value, curSegmentLength, curMaxSegmentLength = -1, numOfSegments = 0;
    cin >> numOfArrays;
    for (int i = 0; i < numOfArrays; ++i) {
        cin >> arrayLength;
        curSegmentLength = 0;
        curMaxSegmentLength = -1;
        numOfSegments = 0;
        vector<int> lengths;
        for (int j = 0; j < arrayLength; ++j) {
            cin >> value;
            if (value <= curSegmentLength) {
                lengths.emplace_back(curSegmentLength);
                curMaxSegmentLength = -1;
                curSegmentLength = 0;
                ++numOfSegments;
            }
            if (curMaxSegmentLength == -1) {
                curMaxSegmentLength = value;
            }
            else {
                curMaxSegmentLength = min(curMaxSegmentLength, value);
            }
            ++curSegmentLength;
            if (curMaxSegmentLength == curSegmentLength) {
                lengths.emplace_back(curSegmentLength);
                curMaxSegmentLength = -1;
                curSegmentLength = 0;
                ++numOfSegments;
            }
        }
        if (curMaxSegmentLength != -1) {
            lengths.emplace_back(curSegmentLength);
            ++numOfSegments;
        }
        cout << numOfSegments << endl;
        for (int length: lengths) {
            cout << length << " ";
        }
        cout << endl;
    }
}

int main() {
    solve();
    return 0;
}

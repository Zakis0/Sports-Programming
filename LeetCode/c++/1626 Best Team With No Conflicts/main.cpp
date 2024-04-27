// https://leetcode.com/problems/best-team-with-no-conflicts/

#include <iostream>
#include <vector>

using namespace std;

int bestTeamScore(vector<int>& scores, vector<int>& ages) {
    int teamScore = 0;
    int youngerAge = ages[0], youngerScore = scores[0], olderAge = ages[0], olderScore = scores[0];
    for (int i = 1; i < scores.size(); ++i) {
        if(ages[i] < youngerAge) {
            youngerAge = ages[i];
            youngerScore = scores[i];
        }
        if(ages[i] > olderAge) {
            olderAge = ages[i];
            olderScore = scores[i];
        }

    }
    cout << youngerAge << " " << youngerScore << endl;
    cout << olderAge << " " << olderScore << endl;
}

int getMinPos(vector<int>& arr, int start = 0) {
    int minPos = start;
    for (int i = start; i < arr.size(); ++i) {
        if (arr[i] < arr[minPos]) {
            minPos = i;
        }
    }
    return minPos;
}

void sort(vector<int>& scores, vector<int>& ages) {
    int temp, scoresMaxPos;
    for (int i = 0; i < scores.size(); ++i) {
        scoresMaxPos = getMinPos(ages, i);

        temp = scores[i];
        scores[i] = scores[scoresMaxPos];
        scores[scoresMaxPos] = temp;

        temp = ages[i];
        ages[i] = ages[scoresMaxPos];
        ages[scoresMaxPos] = temp;
    }
}

int main() {
    vector<int> scores = {
            4,5,6,5
    }, ages = {
            2,1,2,1
    };
    sort(scores, ages);
    for (int i: scores) {
        cout << i << " ";
    }
    cout << endl;
    for (int i: ages) {
        cout << i << " ";
    }
    cout << endl;

//    cout << bestTeamScore(scores, ages) << endl;
    return 0;
}

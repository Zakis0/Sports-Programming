#include <bits/stdc++.h>
using namespace std;

int solve() {
    char c;
    int match1Team1, match1Team2, match2Team1, match2Team2, firstMatchAtGuests;

    cin >> match1Team1 >> c >> match1Team2 >> match2Team1 >> c >> match2Team2 >> firstMatchAtGuests;

    --firstMatchAtGuests;

    int team1Score = match1Team1 + match2Team1;
    int team2Score = match1Team2 + match2Team2;

    int team1GuestScore, team2GuestScore;

    int goalsNeeded = team2Score - team1Score;

    match2Team1 += goalsNeeded;

    if (firstMatchAtGuests) {
        team1GuestScore = match1Team1;
        team2GuestScore = match2Team2;
    }
    else {
        team1GuestScore = match2Team1;
        team2GuestScore = match1Team2;
    }

    if (team2GuestScore >= team1GuestScore) {
        ++goalsNeeded;
    }
    return goalsNeeded;
}

int main() {
    cout << max(solve(), 0);
    return 0;
}

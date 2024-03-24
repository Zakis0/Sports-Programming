#define DEBUG
#define LOCAL_RUN
//#define PRINT_TIME

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

const int MIN_MINUTE = 1;
const int MAX_MINUTE = 90;

struct Team {
    int totalGoals, numOfMatches, numOfOpensScore;

    Team() {
        totalGoals = 0;
        numOfMatches = 0;
        numOfOpensScore = 0;
    }

    int getTotalGoals() {
        return totalGoals;
    }
    float getMeanGoalsPerGame() {
        return (float)totalGoals / numOfMatches;
    }
    int getNumOfOpensScore() {
        return numOfOpensScore;
    }
};

struct Player {
    Team* team;
    int totalGoals, numOfOpensScore;
    map<int, int> numOfGoalsAtMinute;
    map<int, int> numOfGoalsAtFirstTMinutes;
    map<int, int> numOfGoalsAtLastTMinutes;

    Player() {
        team = nullptr;
        totalGoals = 0;
        numOfOpensScore = 0;
    }
    
    int getTotalGoals() {
        return totalGoals;
    }
    float getMeanGoalsPerGame() {
        return (float)totalGoals / team->numOfMatches;
    }
    int getGoalsOnMinuteT(int minute) {
        if (numOfGoalsAtMinute.find(minute) == numOfGoalsAtMinute.end()) {
            return 0;
        }
        return numOfGoalsAtMinute[minute];
    }
    int getGoalsOnFirstTMinute(int minute) {
        return numOfGoalsAtFirstTMinutes[minute];
    }
    int getGoalsOnLastTMinute(int minute) {
        return numOfGoalsAtLastTMinutes[91 - minute];
    }
    int getNumOfOpensScore() {
        return numOfOpensScore;
    }
    void addGoal(int minute) {
        ++totalGoals;
        ++team->totalGoals;
        ++numOfGoalsAtMinute[minute];
        updateNumOfGoalsAtFirstLastTMinutes(minute);
    }
    void isOpenScore() {
        ++numOfOpensScore;
    }
private:
    void updateNumOfGoalsAtFirstLastTMinutes(int goalMinute) {
        for (int minute = goalMinute; minute <= MAX_MINUTE; ++minute) {
            ++numOfGoalsAtFirstTMinutes[minute];
        }
        for (int minute = goalMinute; minute >= MIN_MINUTE; --minute) {
            ++numOfGoalsAtLastTMinutes[minute];
        }
    }
};

string parseName(istringstream& iss, string& line, string initString = "") {
    bool read = true;
    string word;
    vector<string> words;
    words.emplace_back(initString);
    if (!initString.ends_with('"')) {
        while (read) {
            if (!(iss >> word)) {
                getline(cin, line);
                iss = istringstream(line);
                break;
            }
            if (word.ends_with('"')) {
                read = false;
            }
            words.emplace_back(word);
        }
    }
    string name = "";
    for (int j = 0; j < words.size(); ++j) {
        name += words[j] + " ";
    }
    name = name.substr(0, name.size() - 1);
    if (name.starts_with(" ")) {
        name = name.substr(1, name.size());
    }
    return name;
}

void parsePlayers(istringstream& iss, map<string, Team>& teams, map<string, Player>& players,
                 int teamScore, string teamName, string& nameOfPlayerThatGetFirstGoalInTeam, int& minuteOfFirstGoalByTeam) {
    string line;
    for (int i = 0; i < teamScore; ++i) {
        bool read = true;
        string param;
        vector<string> params;
        while (read) {
            while (!(iss >> param)) {
                getline(cin, line);
                iss = istringstream(line);
            }
            if (param.ends_with('\'')) {
                param = param.substr(0, param.size() - 1);
                read = false;
            }
            params.emplace_back(param);
        }
        string name = "";
        for (int j = 0; j < params.size() - 1; ++j) {
            name += params[j] + " ";
        }
        name = name.substr(0, name.size() - 1);
        int minuteOfGoal = stoi(params[params.size() - 1]);
        if (players[name].team == nullptr) {
            players[name].team = &teams[teamName];
        }
        if (i == 0) {
            nameOfPlayerThatGetFirstGoalInTeam = name;
            minuteOfFirstGoalByTeam = minuteOfGoal;
        }
        players[name].addGoal(minuteOfGoal);
    }
}

const string TOTAL = "Total";
const string MEAN = "Mean";
const string GOALS = "Goals";
const string SCORE = "Score";

const string MINUTE = "minute";
const string FIRST = "first";
const string LAST = "last";

const string FOR = "for";
const string BY = "by";

void solve() {
    map<string, Team> teams;
    map<string, Player> players;

    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            // if new match info
            if (word.starts_with('"')) {
                string team1Name, team2Name, fillerString;
                char fillerChar;
                int team1Score, team2Score;

                team1Name = parseName(iss, line, word);
                iss >> fillerString;
                team2Name = parseName(iss, line);
                iss >> team1Score >> fillerChar >> team2Score;

                ++teams[team1Name].numOfMatches;
                ++teams[team2Name].numOfMatches;

                string nameOfPlayerThatGetFirstGoalInTeam1 = "";
                string nameOfPlayerThatGetFirstGoalInTeam2 = "";

                int minuteOfFirstGoalByTeam1 = -1;
                int minuteOfFirstGoalByTeam2 = -1;

                parsePlayers(iss, teams, players, team1Score, team1Name, nameOfPlayerThatGetFirstGoalInTeam1, minuteOfFirstGoalByTeam1);
                parsePlayers(iss, teams, players, team2Score, team2Name, nameOfPlayerThatGetFirstGoalInTeam2, minuteOfFirstGoalByTeam2);

                if (minuteOfFirstGoalByTeam1 != -1 && (
                        minuteOfFirstGoalByTeam1 < minuteOfFirstGoalByTeam2 ||
                        minuteOfFirstGoalByTeam2 == -1)) {
                    ++teams[team1Name].numOfOpensScore;
                    ++players[nameOfPlayerThatGetFirstGoalInTeam1].numOfOpensScore;
                }
                if (minuteOfFirstGoalByTeam2 != -1 && (
                        minuteOfFirstGoalByTeam2 < minuteOfFirstGoalByTeam1 ||
                        minuteOfFirstGoalByTeam1 == -1)) {
                    ++teams[team2Name].numOfOpensScore;
                    ++players[nameOfPlayerThatGetFirstGoalInTeam2].numOfOpensScore;
                }
            }
            // if getting info command
            else {
                if (word == TOTAL) {
                    iss >> word >> word;
                    string name = parseName(iss, line);
                    if (word == FOR) {
                        cout << teams[name].getTotalGoals() << endl;
                    }
                    else if (word == BY) {
                        cout << players[name].getTotalGoals() << endl;
                    }
                }
                else if (word == MEAN) {
                    iss >> word >> word >> word >> word;
                    string name = parseName(iss, line);
                    if (word == FOR) {
                        cout << teams[name].getMeanGoalsPerGame() << endl;
                    }
                    else if (word == BY) {
                        cout << players[name].getMeanGoalsPerGame() << endl;
                    }
                }
                else if (word == GOALS) {
                    int minute;
                    string type;
                    iss >> word >> type >> minute >> word;
                    if (word != BY) {
                        iss >> word;
                    }
                    string name = parseName(iss, line);
                    if (type == MINUTE) {
                        cout << players[name].getGoalsOnMinuteT(minute) << endl;
                    }
                    else if (type == FIRST) {
                        cout << players[name].getGoalsOnFirstTMinute(minute) << endl;
                    }
                    else if (type == LAST) {
                        cout << players[name].getGoalsOnLastTMinute(minute) << endl;
                    }
                }
                else if (word == SCORE) {
                    iss >> word >> word;
                    string name = parseName(iss, line);
                    if (name.starts_with('"')) {
                        cout << teams[name].getNumOfOpensScore() << endl;
                    }
                    else {
                        cout << players[name].getNumOfOpensScore() << endl;
                    }
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
    std::cout << "_____________________________" << endl <<
    "The time: " << (ld)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
#endif
    return 0;
}

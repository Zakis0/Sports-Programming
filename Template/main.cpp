#include <bits/stdc++.h>

#define PRINT_TIME
//#define READ_FROM_FILE

#ifdef READ_FROM_FILE
#define cin fin
#endif

#define first x
#define second y

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

using ll [[maybe_unused]] = long long;
using ld [[maybe_unused]] = double;

using namespace std;

void solve(ifstream& fin) {

}

int main() {
    // Time measure
    time_t start, end;
    time(&start);
    // Read from file
    ifstream fin("input.txt");
    // Float precision
    cout << setprecision(20);

    // Starting solution
    solve(fin);

    time(&end);
#ifdef PRINT_TIME
    cout << endl << "The time: " << difftime(end, start) << " seconds" << endl;
#endif
    return 0;
}

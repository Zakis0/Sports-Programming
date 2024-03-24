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

const string YES = "YES";
const string NO = "NO";

class Multiset {
    map<int, int> numOfValues;
public:
    void insert(int value) {
        ++numOfValues[value];
    }
    void erase(int value) {
        if (numOfValues[value] > 0) {
            --numOfValues[value];
        }
    }
    bool contains(int value) {
        return numOfValues[value] > 0;
    }
};

class Queue {
private:
    int size, front_, rear, maxSize;
    int* queue;

    Multiset valuesSet;

    void inc(int &n) {
        n = (n + maxSize + 1) % maxSize;
    }
public:
    explicit Queue(int maxSize = 1024) {
        size = 0;
        front_ = 0;
        rear = 0;
        this->maxSize = maxSize;
        queue = new int[this->maxSize];
    }
    ~Queue() {
        delete[] queue;
    }
    bool isEmpty() const {
        return size == 0;
    }
    bool isFull() const {
        return size == maxSize;
    }
    int front() {
        if (!isEmpty()) {
            return queue[front_];
        }
        else {
            cerr << "Queue is empty" << endl;
        }
    }
    void pop() {
        if (!isEmpty()) {
            valuesSet.erase(queue[front_]);
            inc(front_);
            --size;
        }
        else {
            cerr << "Queue is empty" << endl;
        }
    }
    void push(int n) {
        if (!isFull()) {
            valuesSet.insert(n);
            queue[rear] = n;
            inc(rear);
            ++size;
        }
        else {
            cerr << "Queue is full" << endl;
        }
    }
    int getAndPop() {
        if (!isEmpty()) {
            int f = front();
            inc(front_);
            --size;
            return f;
        }
        else {
            cerr << "Queue is empty" << endl;
        }
    }
    int getSize() const {
        return size;
    }
    int getMaxSize() const {
        return maxSize;
    }
    int* getQueue() {
        int* arr = new int[size];
        int pos = front_;
        for (int i = 0; i < size; ++i) {
            arr[i] = queue[pos];
            pos = (pos + maxSize + 1) % maxSize;
        }
        return arr;
    }
    bool contains(int value) {
        return valuesSet.contains(value);
    }

    friend ostream& operator<<(ostream& out, Queue& queue) {
        int* arr = queue.getQueue();
        for (int i = 0; i < queue.size; ++i) {
            cout << arr[i] << " ";
        }
        delete[] arr;
        return out;
    }
};

void solve() {
    int n, k, number;
    cin >> n >> k;
    Queue lastKNumbers(k + 1);
    for (int i = 0; i < n; ++i) {
        cin >> number;
        if (i > k) {
            lastKNumbers.pop();
        }
        if (lastKNumbers.contains(number)) {
            cout << YES;
            return;
        }
        lastKNumbers.push(number);
    }
    cout << NO;
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

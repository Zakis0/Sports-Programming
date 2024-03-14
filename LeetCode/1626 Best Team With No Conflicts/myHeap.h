#ifndef INC_1626_BEST_TEAM_WITH_NO_CONFLICTS_MYHEAP_H
#define INC_1626_BEST_TEAM_WITH_NO_CONFLICTS_MYHEAP_H

#include <iostream>

using namespace std;

class Heap {
    int* arr;
    int size;
    int maxSize;

    void error(string str);
public:
    Heap(int maxSize);
    ~Heap();
    int getMax();
    void add(int value);
    void delMax();
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;
    int getMaxSize() const;
    void printHeap() const;
    static void heapSort(int* arr, int arrSize);
};

#endif //INC_1626_BEST_TEAM_WITH_NO_CONFLICTS_MYHEAP_H

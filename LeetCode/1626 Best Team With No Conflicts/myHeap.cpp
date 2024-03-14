#include "myHeap.h"

Heap::Heap(int maxSize) {
    size = 0;
    this->maxSize = maxSize;
    arr = new int[this->maxSize];
}

Heap::~Heap() {
    delete[] arr;
}

int Heap::getMax() {
    if (!isEmpty()) {
        return arr[0];
    }
    error("Heap is empty");
}

void Heap::add(int value) {
    if (isFull()) {
        error("Heap is full");
    }
    int temp;
    int cur = size;
    int top = (cur - 1) / 2;

    arr[size++] = value;
    if (size == 1) {
        return;
    }

    while (arr[top] < arr[cur]) {
        temp = arr[top];
        arr[top] = arr[cur];
        arr[cur] = temp;
        cur = top;
        top = (cur - 1) / 2;
    }
}

void Heap::delMax() {
    if (isEmpty()) {
        error("Heap is empty");
    }
    if (size == 1)  {
        --size;
        return;
    }
    arr[0] = arr[--size];
    int cur = 0;
    int left = cur * 2 + 1;
    int right = cur * 2 + 2;
    int temp;
    while (true) {
        if (left < size && arr[left] > arr[cur] && (right >= size || (right < size && arr[left] > arr[right]))) {
            temp = arr[cur];
            arr[cur] = arr[left];
            arr[left] = temp;
            cur = left;
            left = cur * 2 + 1;
            right = cur * 2 + 2;
        }
        else if (right < size && arr[right] > arr[cur] && arr[right] > arr[left]) {
            temp = arr[cur];
            arr[cur] = arr[right];
            arr[right] = temp;
            cur = right;
            left = cur * 2 + 1;
            right = cur * 2 + 2;
        }
        else {
            break;
        }
    }
}

bool Heap::isEmpty() const {
    return size == 0;
}

bool Heap::isFull() const {
    return size == maxSize;
}

int Heap::getSize() const {
    return size;
}

int Heap::getMaxSize() const {
    return maxSize;
}

void Heap::printHeap() const {
    int step = 1, dStep = 2;
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
        if (--step == 0) {
            step += dStep;
            dStep *= 2;
            cout << endl;
        }
    }
    cout << endl;
}

void Heap::error(string str) {
    cerr << str << endl;
    exit(-1);
}

void Heap::heapSort(int *arr, int arrSize) {
    Heap heap(arrSize);
    for (int i = 0; i < arrSize; ++i) {
        heap.add(arr[i]);
    }
    for (int i = arrSize - 1; i >= 0; --i) {
        arr[i] = heap.getMax();
        heap.delMax();
    }
}

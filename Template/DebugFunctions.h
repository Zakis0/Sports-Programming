#ifndef TEMPLATE_READY_FUNCTIONS_H
#define TEMPLATE_READY_FUNCTIONS_H

#include <vector>
#include <iostream>

using namespace std;

template<class T> struct DebugFunctions {
    static void printVector(vector<T> vec, bool needLineBreak = true, const string& separator = " ");
    static void printMatrix(vector<vector<T>> matrix, bool needLineBreak = true, const string& separator = " ");
};

#endif //TEMPLATE_READY_FUNCTIONS_H

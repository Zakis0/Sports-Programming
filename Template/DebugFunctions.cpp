#include "DebugFunctions.h"

template<class T>
void DebugFunctions<T>::printVector(vector<T> vec, bool needLineBreak, const string &separator) {
    if (vec.empty()) {
        cout << "Vector is empty";
    }
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i != vec.size() - 1 ? separator : "");
    }
    if (needLineBreak) {
        cout << endl;
    }
}

template<class T>
void DebugFunctions<T>::printMatrix(vector<vector<T>> matrix, bool needLineBreak, const string &separator) {
    if (matrix.empty()) {
        cout << "Matrix is empty";
    }
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            cout << matrix[i][j] << (j != matrix[0].size() - 1 ? separator : "");
        }
        cout << endl;
    }
    if (needLineBreak) {
        cout << endl;
    }
}
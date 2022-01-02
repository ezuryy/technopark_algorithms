// Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел
// B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс элемента
// массива A[k], ближайшего по значению к B[i].
// Требования: Время работы поиска для каждого элемента B[i]: O(log(k)).

#include <iostream>

using std::cin;
using std::cout;

void ExponentialSearch(const int* array, const size_t& size, const int& target, size_t& left, size_t& right ) {
    while (right < size && array[right] < target) {
        left = right;
        right <<= 1;
    }
    if (right >= size) {
        right = size - 1;
    }
}

size_t BinarySearch(const int* array, const size_t& size, const int& target, size_t left, size_t right) {
    if (size == 0 || left >= size) {
        return 0;
    }
    if (right >= size) {
        right = size - 1;
    }
    size_t middle;
    while (left < right) {
        middle = (left + right) / 2;
        if (array[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

size_t FindTwin(const int* array, const size_t& size, const int& target) {
    if (size == 1) {
        return 0;
    }
    size_t leftBound = 0;
    size_t rightBound = 1;

    ExponentialSearch(array, size, target, leftBound, rightBound);

    size_t left = BinarySearch(array, size, target, leftBound, rightBound);

    if (left == 0) {
        return 0;
    }

    if (target - array[left - 1] <= array[left] - target) {
        left--;
    }
    return left;
}


int main() {
    size_t sizeA = 0;
    cin >> sizeA;
    int* A = new int[sizeA];

    for (size_t i = 0; i < sizeA; ++i) {
        cin >> A[i];
    }

    size_t sizeB = 0;
    cin >> sizeB;
    int* B = new int[sizeB];

    for (size_t i = 0; i < sizeB; ++i) {
        cin >> B[i];
    }

    for (size_t i = 0; i < sizeB; ++i) {
        cout << FindTwin(A, sizeA, B[i]);
        if (i + 1 < sizeB) {
            cout << " ";
        }
    }

    delete[] A;
    delete[] B;
    return 0;
}

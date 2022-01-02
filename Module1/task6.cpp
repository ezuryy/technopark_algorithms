// Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте
// методом прохода двумя итераторами от начала массива к концу.
//
// Дано множество целых чисел из [0, 10^9] размера n.
// Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
// 1)	10%  перцентиль
// 2)	медиана
// 3)	90%  перцентиль
//
// Требования:
// - Дополнительная память: O(n)
// - Среднее время работы: O(n)
// - Должна быть отдельно выделенная функция partition
// - Рекурсия запрещена
// - Решение должно поддерживать передачу функции сравнения снаружи

#include <cmath>
#include <iostream>

template <typename T>
bool IsLessDefault(const T& lhs, const T& rhs) {
    return lhs < rhs;
}

size_t MedianOfThree(int* arr, const size_t& left, const size_t& right,
                     bool isLess(const int&, const int&) = IsLessDefault<int>) {
    size_t mid = floor((left + right) / 2);
    if (isLess(arr[right], arr[left])) {
        std::swap(arr[left], arr[right]);
    }
    if (isLess(arr[mid], arr[left])) {
        std::swap(arr[mid], arr[left]);
    }
    if (isLess(arr[right], arr[mid])) {
        std::swap(arr[right], arr[mid]);
    }
    return mid;
}

size_t Partition(int* arr, const size_t& left, const size_t& right,
                 bool isLess(const int&, const int&) = IsLessDefault<int>) {
    size_t pivotInd = MedianOfThree(arr, left, right, isLess);
    int pivot = arr[pivotInd];
    std::swap(arr[pivotInd], arr[right]);
    size_t i = left;
    size_t j = left;
    while (true) {
        while (i < right && (isLess(arr[i], pivot) || arr[i] == pivot)) {
            ++i;
        }
        while (j < right && isLess(pivot, arr[j]) || j < i) {
            ++j;
        }
        if (j < right && isLess(arr[j], arr[i])) {
            std::swap(arr[i], arr[j]);
            ++i;
            ++j;
        } else {
            std::swap(arr[i], arr[right]);
            return i;
        }
    }
}

int KStatistic(int* arr, size_t left, size_t right, const size_t& k,
               bool isLess(const int&, const int&) = IsLessDefault<int>) {
    size_t pivotPos = Partition(arr, left, right, isLess);
    while (pivotPos != k) {
        if (k < pivotPos) {
            right = pivotPos - 1;
        } else {
            left = pivotPos + 1;
        }
        pivotPos = Partition(arr, left, right, isLess);
    }
    return arr[pivotPos];
}

int main() {
    size_t size = 0;
    std::cin >> size;
    int* array = new int[size];
    for (size_t i = 0; i < size; ++i) {
        std::cin >> array[i];
    }
    size_t percentile[] = {10, 50, 90};
    for (size_t perc : percentile) {
        std::cout << KStatistic(array, 0, size - 1, perc * size / 100, IsLessDefault) << "\n";
    }

    delete[] array;
    return 0;
}

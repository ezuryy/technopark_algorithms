// На числовой прямой окрасили N отрезков.
// Известны координаты левого и правого концов каждого отрезка [Li, Ri].
// Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
// N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].

#include <cmath>
#include <iostream>

struct Point {
    int coordinate;
    int difference;
};

bool IsLessDefault(const Point& lhs, const Point& rhs) {
    return lhs.coordinate < rhs.coordinate;
}

void Merge(Point* array, const size_t& left, const size_t& middle,
           const size_t& right, Point* result,
           bool isLess(const Point&, const Point&) = IsLessDefault) {
    size_t size = right - left + 1;
    size_t leftIndex = left;
    size_t rightIndex = middle;
    for (size_t k = 0; k < size; ++k) {
        if (leftIndex < middle && rightIndex <= right) {
            if (isLess(array[leftIndex], array[rightIndex])) {
                result[k] = array[leftIndex];
                ++leftIndex;
            } else {
                result[k] = array[rightIndex];
                ++rightIndex;
            }
        } else if (leftIndex < middle) {
            result[k] = array[leftIndex];
            ++leftIndex;
        } else {
            result[k] = array[rightIndex];
            ++rightIndex;
        }
    }
}

void MergeSort(Point* array, const size_t& left, const size_t& right,
               bool isLess(const Point&, const Point&) = IsLessDefault) {
    if (right - left < 1) {
        return;
    }
    size_t middle = ceil(float(left + right) / 2.);
    MergeSort(array, left, middle - 1, isLess);
    MergeSort(array, middle, right, isLess);
    size_t size = right - left + 1;
    auto* result = new Point[size];
    Merge(array, left, middle, right, result, isLess);
    std::copy(result, result + size, array + left);
    delete[] result;
}

int PaintedInOneLayer(const Point* points, const size_t& size) {
    int layers = 1;
    int counter = 0;
    for (size_t i = 1; i < size; ++i) {
        if (layers == 1) {
            counter += (points[i].coordinate - points[i - 1].coordinate);
        }
        layers += points[i].difference;
    }
    return counter;
}

int main() {
    size_t segmentCount = 0;
    std::cin >> segmentCount;
    size_t size = 2 * segmentCount;
    auto* points = new Point[size];
    for (size_t i = 0; i < size; ++i) {
        std::cin >> points[i].coordinate;
        points[i].difference = 1;
        ++i;
        std::cin >> points[i].coordinate;
        points[i].difference = -1;
    }

    MergeSort(points, 0, size - 1, IsLessDefault);

    std::cout << PaintedInOneLayer(points, size) << std::endl;

    delete[] points;
    return 0;
}

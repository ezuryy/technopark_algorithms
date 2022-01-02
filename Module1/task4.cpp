// Напишите программу, которая использует кучу для слияния K отсортированных
// массивов суммарной длиной N.
//
// Требования:
// - Время работы O(N * logK)
// - Куча должна быть реализована в виде шаблонного класса.
// - Решение должно поддерживать передачу функции сравнения снаружи.
// - Куча должна быть динамической.

#include <cmath>
#include <iostream>

using std::cin;
using std::cout;

template <typename T>
class IsLessDefault {
   public:
    bool operator()(const T& lhs, const T& rhs) { return lhs < rhs; }
};

template <typename K, typename V>
struct Pair {
    K first;
    V second;

    Pair() = default;
    Pair(K key, V value) : first(key), second(value) {}
    ~Pair() = default;
};

struct Element {
    int key;
    size_t arrayIndex;

    Element() = default;
    Element(const int& k, const size_t& index) : key(k), arrayIndex(index) {}
    ~Element() = default;
};

bool operator<(const Element& lhs, const Element& rhs) {
    return lhs.key < rhs.key;
}

template <typename T, typename IsLess>
class Heap {
   private:
    size_t getParent(const size_t& index) const;

    size_t getLeftChild(const size_t& index) const;

    size_t getRightChild(const size_t& index) const;

    void downHeapify(const size_t& index);

    void upHeapify(const size_t& index);

   public:
    Heap(const IsLess& less = IsLessDefault<T>())
        : size(0), capacity(0), array(nullptr), isLess(less){};

    Heap(const size_t& heapSize, const size_t& heapCapacity, const T* heap,
         const IsLess& less = IsLessDefault<T>()) = delete;

    ~Heap() { delete[] array; }

    void add(const T& element);

    T extract();

   protected:
    size_t size;
    size_t capacity;
    T* array;
    IsLess isLess;
};

template <typename T, typename IsLess>
size_t Heap<T, IsLess>::getParent(const size_t& index) const {
    if (index == 0) {
        return 0;
    }
    return std::floor((index - 1) / 2);
}

template <typename T, typename IsLess>
size_t Heap<T, IsLess>::getLeftChild(const size_t& index) const {
    return 2 * index + 1;
}

template <typename T, typename IsLess>
size_t Heap<T, IsLess>::getRightChild(const size_t& index) const {
    return 2 * index + 2;
}

template <typename T, typename IsLess>
void Heap<T, IsLess>::downHeapify(const size_t& index) {
    size_t current_ind = index;
    size_t left_ind = getLeftChild(current_ind);
    size_t right_ind = getRightChild(current_ind);

    while (
        current_ind < size / 2 &&
        (isLess(array[left_ind], array[current_ind]) ||
         (right_ind < size && isLess(array[right_ind], array[current_ind])))) {
        if (right_ind >= size || isLess(array[left_ind], array[right_ind])) {
            std::swap(array[left_ind], array[current_ind]);
            current_ind = left_ind;
        } else {
            std::swap(array[right_ind], array[current_ind]);
            current_ind = right_ind;
        }

        left_ind = getLeftChild(current_ind);
        right_ind = getRightChild(current_ind);
    }
}

template <typename T, typename IsLess>
void Heap<T, IsLess>::upHeapify(const size_t& index) {
    size_t current_ind = index;
    size_t parent_ind = getParent(current_ind);

    while (current_ind != 0 && isLess(array[current_ind], array[parent_ind])) {
        std::swap(array[parent_ind], array[current_ind]);
        current_ind = parent_ind;
        parent_ind = getParent(current_ind);
    }
}

template <typename T, typename IsLess>
void Heap<T, IsLess>::add(const T& element) {
    if (capacity == 0) {
        capacity = 1;
        array = new T[capacity];
    } else if (size == capacity) {
        capacity *= 2;
        T* newArray = new T[capacity];
        std::copy(array, array + size, newArray);
        delete[] array;
        array = newArray;
    }
    array[size] = element;
    ++size;

    upHeapify(size - 1);
}

template <typename T, typename IsLess>
T Heap<T, IsLess>::extract() {
    if (size == 0) {
        throw std::invalid_argument("min heap is empty");
    }
    std::swap(array[0], array[size - 1]);
    T result = array[size - 1];
    --size;
    downHeapify(0);
    return result;
}

Pair<int*, size_t> merge(const size_t k, const size_t* arraySize, int** array) {
    size_t size = 0;
    for (size_t i = 0; i < k; ++i) {
        size += arraySize[i];
    }
    int* result = new int[size];

    Heap<Element, IsLessDefault<Element>> heap;
    for (size_t i = 0; i < k; ++i) {
        if (arraySize[i] > 0) {
            heap.add(Element(array[i][0], i));
        }
    }

    auto* counter = new size_t[k];
    for (size_t i = 0; i < k; ++i) {
        counter[i] = 1;
    }

    for (size_t i = 0; i < size; ++i) {
        auto minElement = heap.extract();
        int element = minElement.key;
        size_t arrayInd = minElement.arrayIndex;
        result[i] = element;
        if (counter[arrayInd] < arraySize[arrayInd]) {
            heap.add(Element(array[arrayInd][counter[arrayInd]], arrayInd));
            ++counter[arrayInd];
        }
    }
    delete[] counter;
    return {result, size};
}

int main() {
    size_t arrayCount = 0;

    cin >> arrayCount;
    int** array = new int*[arrayCount];
    auto* arraySize = new size_t[arrayCount];

    for (size_t i = 0; i < arrayCount; ++i) {
        cin >> arraySize[i];
        array[i] = new int[arraySize[i]];
        for (size_t j = 0; j < arraySize[i]; ++j) {
            cin >> array[i][j];
        }
    }

    auto result = merge(arrayCount, arraySize, array);

    for (size_t i = 0; i < result.second; ++i) {
        cout << result.first[i] << " ";
    }

    for (size_t i = 0; i < arrayCount; ++i) {
        delete[] array[i];
    }
    delete[] array;
    delete[] arraySize;
    delete[] result.first;
    return 0;
}

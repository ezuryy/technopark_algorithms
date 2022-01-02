// Дан массив строк. Количество строк не больше 100000.
// Отсортировать массив методом поразрядной сортировки MSD по символам.
// Размер алфавита - 256 символов. Последний символ строки = '\0'

#include <cassert>
#include <iostream>

using std::string;

void print(string* array, size_t size) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << "\n";
    }
}

int getCodeOfChar(const string& str, const size_t& d) {
    if (str.size() <= d) {
        return -1;
    } else {
        return str[d];
    }
}

size_t getMaxRank(const string* array, const size_t& left,
                  const size_t& right) {
    size_t maximum = 0;
    for (size_t i = left; i <= right; ++i) {
        if (array[i].size() > maximum) {
            maximum = array[i].size();
        }
    }
    return maximum;
}

void MSD(string* array, const int& left, const int& right, const size_t& rank,
         const size_t& maxRank, const size_t& alphabetSize) {
    if (rank >= maxRank || left >= right) {
        return;
    }
    int* counter = new int[alphabetSize + 2];
    assert(counter);

    // k - счетчик для прохода по алфавиту
    for (size_t k = 0; k < alphabetSize + 2; ++k) {
        counter[k] = 0;
    }
    // i - счетчик для прохода по строкам
    // считаем кол-во вхождений каждого символа в текущем разряде rank
    for (size_t i = left; i <= right; ++i) {
        int codeOfSymbol = getCodeOfChar(array[i], rank);
        ++counter[codeOfSymbol + 1];
    }

    // находим индексы, являющиеся концами промежутков с одинаковыми символами
    for (size_t k = 1; k < alphabetSize + 2; ++k) {
        counter[k] += counter[k - 1];
    }

    auto* newVec = new string[right - left + 1];
    assert(newVec);

    // в новый массив записываем слова, отсортированные внутри кармашка [left,
    // right]
    for (int i = right; i >= left; --i) {
        int codeOfSymbol = getCodeOfChar(array[i], rank);
        newVec[--counter[codeOfSymbol + 1]] = array[i];
    }

    // заменяем старый кармашек на новый отсортированный
    for (size_t i = left; i <= right; ++i) {
        array[i] = newVec[i - left];
    }

    // вызываем MSD для каждого кармашка для следующего разряда
    for (int k = 0; k < 256; ++k) {
        MSD(array, left + counter[k], left + counter[k + 1] - 1, rank + 1,
            maxRank, alphabetSize);
    }
    delete[] counter;
    delete[] newVec;
}

int main() {
    size_t capacity = 2;
    size_t size = 0;
    auto* array = new string[capacity];
    string word;

    while (!std::cin.eof()) {
        std::cin >> word;
        if (!word.empty()) {
            if (size == capacity) {
                capacity *= 2;
                auto* newArray = new string[capacity];
                std::copy(array, array + size, newArray);
                delete[] array;
                array = newArray;
            }
            array[size++] = word;
        }
        word.clear();
    }

    int right = static_cast<int>(size) - 1;

    MSD(array, 0, right, 0, getMaxRank(array, 0, right), 256);

    print(array, size);
    delete[] array;
    return 0;
}

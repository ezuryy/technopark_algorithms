// Реализовать очередь с динамическим зацикленным буфером.
// Обрабатывать команды push back и pop front.

#include <iostream>

class Queue {
   public:
    Queue() : capacity(0), size(0), head(0), tail(0), array(nullptr) {}

    ~Queue() { delete[] array; }

    void push(const int& x);

    int pop();

   private:
    size_t capacity;
    size_t size;
    size_t head;
    size_t tail;
    int* array;
};

void Queue::push(const int& x) {
    if (capacity == 0) {
        capacity = 1;
        tail = capacity - 1;
        array = new int[capacity];
    } else if (size == capacity) {
        int* newArray = new int[2 * capacity];
        if (head <= tail) {
            std::copy(array + head, array + tail + 1, newArray);
        } else {
            std::copy(array + head, array + capacity, newArray);
            std::copy(array, array + tail + 1, newArray + capacity - head);
        }
        head = 0;
        capacity *= 2;
        tail = size - 1;
        delete[] array;
        array = newArray;
    }
    if (tail + 1 == capacity) {
        tail = 0;
    } else {
        tail++;
    }
    array[tail] = x;
    size++;
}

int Queue::pop() {
    if (size == 0) {
        return -1;
    }
    size--;
    if (head + 1 == capacity) {
        head = 0;
        return array[capacity - 1];
    }
    return array[head++];
}

void commandHandler(Queue& queue, const size_t& command, const int& element,
                    bool& isOk) {
    if (command == 3) {
        queue.push(element);
    } else if (command == 2) {
        int popElement = queue.pop();
        if (popElement != element) {
            isOk = false;
        }
    }
}

int main() {
    Queue queue;
    size_t commandCount = 0;
    std::cin >> commandCount;
    size_t command = 0;
    int element = 0;
    bool isOk = true;
    for (size_t i = 0; i < commandCount; ++i) {
        std::cin >> command >> element;
        commandHandler(queue, command, element, isOk);
    }
    std::cout << (isOk ? "YES" : "NO");
    return 0;
}

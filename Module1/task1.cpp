// Если в числе содержится только один бит со значением 1,
// записать в выходной поток OK. Иначе записать FAIL.
//
// Необходимо использование битовых операций.
// Использование арифметических операций запрещено.

#include <iostream>

bool IsPowerOfTwo(size_t number) {
    while ((number & 1) == 0 && number > 0) {
        number >>= 1;
    }
    return number == 1;
}

int main() {
    size_t number = 0;
    std::cin >> number;
    std::cout << (IsPowerOfTwo(number) ? "OK" : "FAIL");
    return 0;
}

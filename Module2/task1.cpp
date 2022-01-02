// Реализуйте структуру данных типа “множество строк” на основе
// динамической хеш-таблицы с открытой адресацией. Хранимые строки
// непустые и состоят из строчных латинских букв. Хеш-функция строки
// должна быть реализована с помощью вычисления значения многочлена методом Горнера.
// Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте
// при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
// Структура данных должна поддерживать операции добавления строки в множество,
// удаления строки из множества и проверки принадлежности данной строки множеству.
// 1_1. Для разрешения коллизий используйте квадратичное пробирование.
// i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

struct Hasher {
    size_t operator() (const string& str) const {
        size_t hash = 0;
        for (const char& symbol : str) {
            hash = hash * 17 + symbol;
        }
        return hash;
    }
};

template <typename T, typename H>
class HashTable {
public:
    explicit HashTable(const H& _hasher) : hasher(_hasher), size(0) {
        table.resize(8);
    }
    HashTable(const HashTable<T, H>& table) = delete;
    HashTable& operator=(const HashTable& table) = delete;
    ~HashTable() = default;

    bool add(const T& value);
    bool find(const T& value);
    bool remove(const T& value);
private:
    struct Node {
        T value;
        size_t hash;
        enum State {
            empty,
            deleted,
            key
        } state;

        Node() : hash(0), state(empty) {}
        Node(T _value, const size_t& _hash) : value(std::move(_value)), hash(_hash), state(key) {}
        ~Node() = default;
    };

    void reserve();

    H hasher;
    vector<Node> table;
    size_t size;
};

template <typename T, typename H>
bool HashTable<T, H>::add(const T& value) {
    if ((float)size >= 0.75 * (float)table.size()) {
        reserve();
    }

    int firstDelPosition = -1;
    size_t absHash = hasher(value);
    size_t hash = absHash % table.size();
    size_t counter = 0;
    while (table[hash].state != Node::empty && counter < table.size()) {
        if (table[hash].state == Node::deleted && firstDelPosition == -1) {
            firstDelPosition = static_cast<int>(hash);
        }
        if (table[hash].value == value && table[hash].state != Node::deleted) {
            return false;
        }
        hash = (hash + counter + 1) % table.size();
        ++counter;
    }
    hash = ((firstDelPosition == -1) ? hash : firstDelPosition);
    table[hash] = Node(std::move(value), absHash);
    ++size;
    return true;
}

template <typename T, typename H>
bool HashTable<T, H>::find(const T& value) {
    size_t hash = hasher(value) % table.size();
    size_t counter = 0;
    while (table[hash].state != Node::empty && counter < table.size()) {
        if (table[hash].value == value && table[hash].state != Node::deleted) {
            return true;
        }
        hash = (hash + counter + 1) % table.size();
        ++counter;
    }
    return false;
}

template <typename T, typename H>
bool HashTable<T, H>::remove(const T& value) {
    size_t hash = hasher(value) % table.size();
    size_t counter = 0;
    while (table[hash].state != Node::empty && counter < table.size()) {
        if (table[hash].value == value && table[hash].state != Node::deleted) {
            table[hash].state = Node::deleted;
            return true;
        }
        hash = (hash + counter + 1) % table.size();
        ++counter;
    }
    return false;
}

template <typename T, typename H>
void HashTable<T, H>::reserve() {
    vector<Node> newTable(table.size() * 2);
    for (const auto& node : table) {
        if (node.state == Node::key) {
            size_t hash = node.hash % newTable.size();
            size_t counter = 0;
            while (newTable[hash].state != Node::empty) {
                hash = (hash + counter + 1) % newTable.size();
                ++counter;
            }
            newTable[hash] = node;
        }
    }
    table = std::move(newTable);
}

int main() {
    char command;
    string value;
    Hasher hasher;
    HashTable<string, Hasher> hashTable(hasher);
    while (!std::cin.eof()) {
        std::cin >> command >> value;
        switch(command) {
            case '+':
                std::cout << ( hashTable.add( value ) ? "OK\n" : "FAIL\n" );
                break;
            case '-':
                std::cout << ( hashTable.remove( value ) ? "OK\n" : "FAIL\n" );
                break;
            case '?':
                std::cout << ( hashTable.find( value ) ? "OK\n" : "FAIL\n" );
                break;
            default:
                break;
        }
        command = ' ';
        value.clear();
    }
    return 0;
}

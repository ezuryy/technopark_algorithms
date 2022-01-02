// Дано число N ≤ 10^4 и последовательность целых чисел из [-231..231] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Выведите элементы в порядке post-order (снизу вверх). Рекурсия запрещена.

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using std::stack;
using std::vector;

template<typename T>
class IsLessDefault {
public:
    bool operator()(const T &lhs, const T &rhs) { return lhs < rhs; }
};

template<typename IsLess>
class BinaryTree {
public:
    explicit BinaryTree(const IsLess &less = IsLessDefault<int>()) : root(nullptr), isLess(less) {}

    ~BinaryTree() {
        deleter(root);
    }

    void insert(const int &value);

    void postOrderTraversal(void visit(const int &));

private:
    struct Node {
        int value;
        Node *parent;
        Node *left;
        Node *right;

        Node() : parent(nullptr), left(nullptr), right(nullptr), value(0) {}

        Node(Node *p, Node *l, Node *r, const int &v)
                : parent(p), left(l), right(r), value(v) {
        }

        ~Node() = default;
    };

    void deleter(Node *node) {
        stack<Node *> nodesStack;
        while (node != nullptr || !nodesStack.empty()) {
            while (node != nullptr) {
                nodesStack.push(node);
                node = node->left;
            }
            node = nodesStack.top()->right;
            Node *removing = nodesStack.top();
            nodesStack.pop();
            delete removing;
        }
    }

    Node *root;
    IsLess isLess;
};

template<typename IsLess>
void BinaryTree<IsLess>::insert(const int &value) {
    if (root == nullptr) {
        root = new Node(nullptr, nullptr, nullptr, value);
        return;
    }

    Node *curr = root;
    while (curr != nullptr) {
        if (isLess(value, curr->value)) {
            if (curr->left == nullptr) {
                curr->left = new Node(curr, nullptr, nullptr, value);
                return;
            }
            curr = curr->left;
        } else {
            if (curr->right == nullptr) {
                curr->right = new Node(curr, nullptr, nullptr, value);
                return;
            }
            curr = curr->right;
        }
    }
}

template<typename IsLess>
void BinaryTree<IsLess>::postOrderTraversal(void visit(const int &)) {
    if (root == nullptr) {
        return;
    }
    stack<Node *> nodesStack;
    nodesStack.push(root);
    vector<Node *> visited;
    while (!nodesStack.empty()) {
        Node *curr = nodesStack.top();
        if (curr->left != nullptr && std::find(visited.begin(), visited.end(), curr->left) == visited.end()) {
            nodesStack.push(curr->left);
            continue;
        }
        if (curr->right != nullptr && std::find(visited.begin(), visited.end(), curr->right) == visited.end()) {
            nodesStack.push(curr->right);
            continue;
        }
        if (curr->left == nullptr && curr->right == nullptr) {
            visit(curr->value);
            visited.push_back(curr);
            nodesStack.pop();
            continue;
        }
        visit(curr->value);
        visited.push_back(curr);
        nodesStack.pop();
    }
}

int main() {

    BinaryTree<IsLessDefault<int>> tree;
    int nodeValue = 0;
    size_t count;
    std::cin >> count;
    while (count > 0) {
        std::cin >> nodeValue;
        tree.insert(nodeValue);
        --count;
    }

    tree.postOrderTraversal([](const int &value) {
        std::cout << value << " ";
    });
    return 0;
}

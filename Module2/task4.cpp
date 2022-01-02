// Дано число N и N строк. Каждая строка содержащит команду добавления или
// удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики.
// Команда добавления числа A задается положительным числом A, команда удаления числа A
// задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики
// задается числом k. Требуемая скорость выполнения запроса - O(log n).

#include <iostream>
#include <stack>

class IsLessDefault {
public:
    bool operator()(const int &lhs, const int &rhs) { return lhs < rhs; }
} myIsLess;

struct Node {
    int key;
    unsigned char height;
    int elemNumber;
    Node *parent;
    Node *left;
    Node *right;

    explicit Node(Node *_parent, int _key) : key(_key), height(1), elemNumber(1),
                                             parent(_parent), left(nullptr), right(nullptr) {}
};

template<typename IsLess>
class AVLtree {
public:
    explicit AVLtree(const IsLess &less = IsLessDefault()) : root(nullptr), isLess(less) {}

    ~AVLtree();

    void insert(int key);

    void remove(int key);

    int getStatistic(const int &stat) const;

private:
    unsigned char height(Node *node) const;

    int balanceFactor(Node *node) const;

    void fixHeight(Node *node);

    int getElemNumber(Node *node) const;

    void fixElemNumber(Node *node);

    Node *rotateRight(Node *p);

    Node *rotateLeft(Node *q);

    Node *balance(Node *node);

    Node *insertRecursive(Node *&node, int key);

    std::pair<Node *, Node *> popMin(Node *node);

    Node *removeRecursive(Node *node, int key);

    Node *root;
    IsLess isLess;
};

template<typename IsLess>
AVLtree<IsLess>::~AVLtree() {
    if (root == nullptr) {
        return;
    }
    std::stack<Node *> nodesStack;
    Node *curr = root;
    Node *lastVisited = nullptr;
    while (!nodesStack.empty() || curr != nullptr) {
        if (curr != nullptr) {
            nodesStack.push(curr);
            curr = curr->left;
        } else {
            curr = nodesStack.top();
            if (curr->right != nullptr && lastVisited != curr->right) {
                curr = curr->right;
            } else {
                nodesStack.pop();
                lastVisited = curr;
                delete curr;
                curr = nullptr;
            }
        }
    }
}

template<typename IsLess>
void AVLtree<IsLess>::insert(int key) {
    root = insertRecursive(root, key);
}

template<typename IsLess>
void AVLtree<IsLess>::remove(int key) {
    root = removeRecursive(root, key);
}

template<typename IsLess>
unsigned char AVLtree<IsLess>::height(Node *node) const {
    return node != nullptr ? node->height : 0;
}

template<typename IsLess>
int AVLtree<IsLess>::balanceFactor(Node *node) const {
    return height(node->right) - height(node->left);
}

template<typename IsLess>
void AVLtree<IsLess>::fixHeight(Node *node) {
    unsigned char lHeight = height(node->left);
    unsigned char rHeight = height(node->right);
    node->height = (lHeight > rHeight ? lHeight : rHeight) + 1;
}

template<typename IsLess>
int AVLtree<IsLess>::getElemNumber(Node *node) const {
    return node != nullptr ? node->elemNumber : 0;
}

template<typename IsLess>
void AVLtree<IsLess>::fixElemNumber(Node *node) {
    node->elemNumber = getElemNumber(node->left) + getElemNumber(node->right) + 1;
}

template<typename IsLess>
Node *AVLtree<IsLess>::rotateRight(Node *p) {
    Node *q = p->left;
    p->left = q->right;
    q->right = p;

    fixHeight(p);
    fixElemNumber(p);
    fixHeight(q);
    fixElemNumber(q);
    return q;
}

template<typename IsLess>
Node *AVLtree<IsLess>::rotateLeft(Node *q) {
    Node *p = q->right;
    q->right = p->left;
    p->left = q;

    fixHeight(q);
    fixElemNumber(q);
    fixHeight(p);
    fixElemNumber(p);
    return p;
}

template<typename IsLess>
Node *AVLtree<IsLess>::balance(Node *node) {
    fixHeight(node);
    fixElemNumber(node);
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->right) < 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->left) > 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    return node;
}

template<typename IsLess>
Node *AVLtree<IsLess>::insertRecursive(Node *&node, int key) {
    if (node == nullptr) {
        return node = new Node(nullptr, key);
    }
    if (isLess(key, node->key)) {
        node->left = insertRecursive(node->left, key);
    } else {
        node->right = insertRecursive(node->right, key);
    }
    return balance(node);
}

template<typename IsLess>
std::pair<Node *, Node *> AVLtree<IsLess>::popMin(Node *node) {
    if (node->left == nullptr) {
        return {node->right, node};
    }
    std::pair<Node *, Node *> removingAndMin = popMin(node->left);
    node->left = removingAndMin.first;
    return {balance(node), removingAndMin.second};
}

template<typename IsLess>
Node *AVLtree<IsLess>::removeRecursive(Node *node, int key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (isLess(key, node->key)) {
        node->left = removeRecursive(node->left, key);
    } else if (key == node->key) {
        Node *left = node->left;
        Node *right = node->right;
        delete node;
        if (right == nullptr) {
            return left;
        }
        std::pair<Node *, Node *> min_pair = popMin(right);
        Node *min = min_pair.second;
        min->right = min_pair.first;
        min->left = left;
        return balance(min);
    } else {
        node->right = removeRecursive(node->right, key);
    }
    return balance(node);
}

template<typename IsLess>
int AVLtree<IsLess>::getStatistic(const int &stat) const {
    int result = -1;
    if (stat < getElemNumber(root)) {
        Node *curr = root;
        int i = getElemNumber(root->left);
        while (i != stat) {
            if (stat > i) {
                curr = curr->right;
                i += getElemNumber(curr->left) + 1;
            } else {
                curr = curr->left;
                i -= getElemNumber(curr->right) + 1;
            }
        }
        result = curr->key;
    } else if (getElemNumber(root) == stat) {
        return root->key;
    }
    return result;
}

int main() {
    size_t counter;
    std::cin >> counter;
    AVLtree<IsLessDefault> tree(myIsLess);

    int key;
    int statisticNumber;
    while (counter > 0) {
        std::cin >> key >> statisticNumber;
        if (key > 0) {
            tree.insert(key);
        } else {
            tree.remove(abs(key));
        }
        std::cout << tree.getStatistic(statisticNumber) << "\n";
        --counter;
    }
    return 0;
}

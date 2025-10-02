#include <iostream>
using namespace std;

struct Node {
    double key;
    char val;
    int size;
    Node* left;
    Node* right;
    Node(double k, char v) : key(k), val(v), size(1), left(nullptr), right(nullptr) {}
};

class Mstring {
    Node* root;

    int size(Node* x) const {
        return x ? x->size : 0;
    }

    void update(Node* x) {
        if (x) x->size = 1 + size(x->left) + size(x->right);
    }

    Node* rotateRight(Node* h) {
        Node* x = h->left;
        h->left = x->right;
        x->right = h;
        update(h);
        update(x);
        return x;
    }

    Node* rotateLeft(Node* h) {
        Node* x = h->right;
        h->right = x->left;
        x->left = h;
        update(h);
        update(x);
        return x;
    }

    Node* insert(Node* h, double key, char val) {
        if (!h) return new Node(key, val);
        if (key < h->key) h->left = insert(h->left, key, val);
        else h->right = insert(h->right, key, val);
        update(h);
        return h;
    }

    Node* findMin(Node* x) {
        while (x->left) x = x->left;
        return x;
    }

    Node* remove(Node* h, double key) {
        if (!h) return nullptr;
        if (key < h->key) h->left = remove(h->left, key);
        else if (key > h->key) h->right = remove(h->right, key);
        else {
            if (!h->left) return h->right;
            if (!h->right) return h->left;
            Node* t = h;
            h = findMin(t->right);
            h->right = remove(t->right, h->key);
            h->left = t->left;
        }
        update(h);
        return h;
    }

    Node* select(Node* x, int i) const {
        if (!x) return nullptr;
        int leftSize = size(x->left);
        if (i < leftSize) return select(x->left, i);
        else if (i > leftSize) return select(x->right, i - leftSize - 1);
        else return x;
    }

    void inorder(Node* x) const {
        if (!x) return;
        inorder(x->left);
        if (x->key != 0 && x->key != 1) cout << x->val;
        inorder(x->right);
    }

    double getKeyAt(int i) {
        Node* x = select(root, i + 1);
        return x ? x->key : -1;
    }

public:
    Mstring() {
        root = nullptr;
        root = insert(root, 0.0, '#');
        root = insert(root, 1.0, '#');
    }

    int size() const {
        return size(root) - 2;
    }

    char get(int i) {
        Node* x = select(root, i + 1);
        return x ? x->val : '?';
    }

    void insert(int i, char c) {
        double leftKey = getKeyAt(i - 1);
        double rightKey = getKeyAt(i);
        double newKey = (leftKey + rightKey) / 2.0;
        root = insert(root, newKey, c);
    }

    void remove(int i) {
        Node* x = select(root, i + 1);
        if (x) root = remove(root, x->key);
    }

    void print() const {
        inorder(root);
        cout << endl;
    }
};

int main() {
Mstring s;
// Insert characters to form "abcd"
s.insert(0, 'a'); s.insert(1, 'b'); s.insert(2, 'c'); s.insert(3, 'd');
std::cout << "String after inserts: "; s.print(); // Expected: abcd
// Get a character
std::cout << "s.get(2) = " << s.get(2) << std::endl; // Expected: c
// Insert in the middle
s.insert(2, 'X');
std::cout << "After insert X at pos 2: "; s.print(); // Expected: abXcd
// Remove a character
s.remove(3);
std::cout << "After remove at pos 3: "; s.print(); // Expected: abXd
// Remove first and last
s.remove(0); s.remove(s.size() - 1);
std::cout << "After removing first and last: "; s.print(); // Expected: bX
}
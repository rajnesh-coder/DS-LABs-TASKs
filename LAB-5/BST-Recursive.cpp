#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k) : key(k), height(0), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;
    int sz , min , max;

    int maxH(int a, int b) {
        return (a > b) ? a : b;
    }

public:
    BST() {
        root = nullptr;
        min = INT_MIN;
        max = INT_MAX;
        sz = 0;
    }

    Node* insert(Node* root, int k) {
        if (root == nullptr) {
            return new Node(k);
        }
        if (k < root->key) {
            root->left = insert(root->left, k);
        } else if (k > root->key) {
            root->right = insert(root->right, k);
        }
        root->height = 1 + maxH(getHeight(root->left), getHeight(root->right));
        return root;
    }

    void insert(int k) {
        root = insert(root, k);
    }

    int getHeight(Node* node) {
        if (node == nullptr) return -1;
        return node->height;
    }

    int height() {
        return getHeight(root);
    }

    int sizeOdd(Node* root) {
        if (root == nullptr) return 0;
        int siz = 0;
        if (root->key % 2 == 1) siz++;
        siz += sizeOdd(root->left);
        siz += sizeOdd(root->right);
        return siz;
    }

    int sizeOdd() {
        return sizeOdd(root);
    }

    bool isPerfectlyBalancedH(Node* root) {
     if (root == nullptr) return true;
     int lh = getHeight(root->left);
     int rh = getHeight(root->right);
     if (lh != rh) return false;
        return isPerfectlyBalancedH(root->left) && isPerfectlyBalancedH(root->right);
    }

    bool isPerfectlyBalancedH() {
        return isPerfectlyBalancedH(root);
    }

    int size(Node* root) {
        if (root == nullptr) return 0;
        return 1 + size(root->left) + size(root->right);
    }

    bool isSemiBalancedI(Node* root) {
    if (root == nullptr) return true;
      if (root->left == nullptr && root->right == nullptr) return true;
        int lsize = size(root->left);
        int rsize = size(root->right);
        int larger = std::max(lsize, rsize);
        int smaller = std::min(lsize, rsize);
     if (smaller == 0) return false;
    if (larger / smaller > 2) return false;
        return isSemiBalancedI(root->left) && isSemiBalancedI(root->right);
    }

    bool isSemiBalancedI() {
        return isSemiBalancedI(root);
    }

    int sizeAtDepth(Node* root, int depth) {
      if (root == nullptr) return 0;
     if (depth == 0) return 1;
        return sizeAtDepth(root->left, depth - 1) + sizeAtDepth(root->right, depth - 1);
    }

    int sizeAtDepth(int depth) {
        return sizeAtDepth(root, depth);
    }

    int sizeAboveDepth(Node* root, int depth) {
    if (root == nullptr) return 0;
    if (depth <= 0) return 0;
        return 1 + sizeAboveDepth(root->left, depth - 1) + sizeAboveDepth(root->right, depth - 1);
    }

    int sizeAboveDepth(int depth) {
        return sizeAboveDepth(root, depth);
    }

    int sizeBelowDepth(Node* root, int depth) {
        if (root == nullptr) return 0;
        if (depth < 0) return size(root);
        if (depth == 0) return size(root->left) + size(root->right);
        return sizeBelowDepth(root->left, depth - 1) + sizeBelowDepth(root->right, depth - 1);
    }

    int sizeBelowDepth(int depth) {
        return sizeBelowDepth(root, depth);
    }


};

int main() {
    BST tree;

    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(69);
    tree.insert(12);
    tree.insert(18);

    cout << "Height: " << tree.height() << endl;
    cout << "Odd keys count: " << tree.sizeOdd() << endl;
    cout << "Perfectly Balanced: " << (tree.isPerfectlyBalancedH() ? "Yes" : "No") << endl;
    cout << "Semi Balanced: " << (tree.isSemiBalancedI() ? "Yes" : "No") << endl;

    for (int d = 0; d <= 3; d++) {
        cout << "Nodes at depth " << d << ": " << tree.sizeAtDepth(d) << endl;
    }

    cout << "Nodes above depth 2: " << tree.sizeAboveDepth(2) << endl;
    cout << "Nodes below depth 1: " << tree.sizeBelowDepth(1) << endl;

    return 0;
}

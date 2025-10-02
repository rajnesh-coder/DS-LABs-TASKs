#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
    Node* root;
    queue<Node*> QI;
    int min, max;

public:
    BST() {
        root = nullptr;
        min = INT_MIN;
        max = INT_MAX;
    }

    Node* insert(int k) {
        if (root == nullptr) {
            root = new Node(k);
            QI.push(root);
            return root;
        }
        while (!QI.empty()) {
            Node* curr = QI.front();
            if (k > min && k < curr->key && curr->left == nullptr) {
                curr->left = new Node(k);
                QI.push(curr->left);
                return root;
            } else if (k < max && k > curr->key && curr->right == nullptr) {
                curr->right = new Node(k);
                QI.push(curr->right);
                return root;
            } else {
                QI.pop();
            }
        }
        return root;
    }

    Node* insert(vector<int>& arr) {
        for (int k : arr) {
            insert(k);
        }
        return root;
    }

    void levelOrderTraversal(Node* root) {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->key << " ";
            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }

    Node* getRoot() {
        return root;
    }
};

int main() {
    BST tree;
    vector<int> arr = {20, 10, 30, 5, 15, 25, 40};
    tree.insert(arr);
    tree.levelOrderTraversal(tree.getRoot());
}

#include <iostream>
#include <vector>
using namespace std;

class set {
    vector<int> key;
public:

    bool contains(int k, int s, int e) {
        if (s > e) {
            return false; 
        }
        int mid = (e + s) / 2;

        if (k == key[mid])
            return true;
        else if (k > key[mid]) {
            return contains(k, mid + 1, e);
        } else {
            return contains(k, s, mid - 1);
        }
    }

    int rank(int k, int s, int e) {
        if (s > e) {
            return s; // insertion position
        }
        int mid = (e + s) / 2;

        if (k == key[mid])
            return mid;
        else if (k > key[mid]) {
            return rank(k, mid + 1, e);
        } else {
            return rank(k, s, mid - 1);
        }
    }

    int ceiling(int k) {
        if (key.empty()) throw runtime_error("Empty set");
        int pos = rank(k, 0, key.size() - 1);
        if (pos >= key.size()) 
            throw runtime_error("No ceiling exists"); // larger than all
        return key[pos];
    }

    int select(int i) {
        return key[i];
    }

    int min() {
        return key[0];
    }

   void add(int k) {
        int sz = key.size();
        if (sz == 0) {
            key.push_back(k);
            return;
        }
        int pos = rank(k, 0, sz - 1);
        if (pos < sz && key[pos] == k) return; // avoid duplicate

        key.push_back(0); // extend size
        for (int i = sz; i > pos; i--) {
            key[i] = key[i - 1];
        }
        key[pos] = k;
    }

    void remove(int k) {
        int sz = key.size();
        if (sz == 0) return;
        int pos = rank(k, 0, sz - 1);
        if (pos < sz && key[pos] == k) {
            for (int i = pos; i < sz - 1; i++) {
                key[i] = key[i + 1];
            }
            key.pop_back(); // shrink size
        }
    }

    void print() {
        for (int v : key) cout << v << " ";
        cout << "\n";
    }
};

int main() {
    set a;
    a.add(10);
    a.add(5);
    a.add(20);
    a.add(15);

    cout << "Set contents: ";
    a.print();

    a.remove(20);
    cout << "Ceiling of 14: " << a.ceiling(14) << "\n";
    cout << "Ceiling of 15: " << a.ceiling(15) << "\n";
    cout << "Ceiling of 21: ";
    try {
        cout << a.ceiling(21) << "\n";
    } catch (exception &e) {
        cout << e.what() << "\n";
    }
}

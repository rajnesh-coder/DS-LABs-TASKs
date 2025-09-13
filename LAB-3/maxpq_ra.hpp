#pragma once
#include <iostream>
#include <stdexcept>
#include <cstdlib>
using namespace std;

template <typename Key>
class MaxPQ {
    int capacity;
    int n;
    Key* pq;

public:
    MaxPQ() : capacity{2}, n{0} {
        pq = new Key[capacity + 1];
    }

    ~MaxPQ() {
        delete[] pq;
    }

    bool empty() { return n == 0; }
    int size() { return n; }

    void resize(int newCapacity) {
        Key* newpq = new Key[newCapacity + 1];
        for (int i = 1; i <= n; i++) {
            newpq[i] = pq[i];
        }
        delete[] pq;
        pq = newpq;
        capacity = newCapacity;
    }

    void insert(Key x) {
        if (n + 1 >= capacity) {
            resize(capacity * 2);
        }
        pq[++n] = x;
        MaxHeapify_Swim(n);
    }

    void MaxHeapify_Sink(int pos) {
        while (pos * 2 <= n) {
            int comp = 2 * pos;
            if (comp < n && pq[comp] < pq[comp + 1]) {
                comp++;
            }
            if (pq[comp] <= pq[pos]) break;
            swap(pq[comp], pq[pos]);
            pos = comp;
        }
    }

    void MaxHeapify_Swim(int pos) {
        while (pos > 1 && pq[pos / 2] < pq[pos]) {
            swap(pq[pos], pq[pos / 2]);
            pos = pos / 2;
        }
    }

    Key delMax() {
        if (n == 0) {
            throw std::runtime_error("Priority queue underflow");
        }
        swap(pq[1], pq[n]);
        Key maxVal = pq[n--];
        MaxHeapify_Sink(1);
        if (n > 0 && n <= capacity / 4) {
            resize(capacity / 2);
        }
        return maxVal;
    }

    Key delRndm() {
        if (n == 0) {
            throw std::runtime_error("Priority queue underflow");
        }
        int rnd = rand() % n + 1;
        swap(pq[rnd], pq[n]);
        Key val = pq[n--];

        MaxHeapify_Sink(rnd);
        MaxHeapify_Swim(rnd);

        if (n > 0 && n <= capacity / 4) {
            resize(capacity / 2);
        }
        return val;
    }

    void Build_maxHeap() {
        for (int i = n / 2; i >= 1; i--) {
            MaxHeapify_Sink(i);
        }
    }

    void Mx_Heapsort() {
        Build_maxHeap();
        int originalN = n;
        while (n > 1) {
            swap(pq[1], pq[n--]);
            MaxHeapify_Sink(1);
        }
        n = originalN; // restore heap size
    }
};

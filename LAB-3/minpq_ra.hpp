#pragma once
#include <iostream>
#include <stdexcept>
#include <cstdlib>
using namespace std;

template <typename Key>
class MinPQ {
    int capacity;
    int n;
    Key* pq;

public:
    MinPQ() : capacity{2}, n{0} {
        pq = new Key[capacity + 1];
    }

    ~MinPQ() {
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
        if (n >= capacity) {
            resize(capacity * 2);
        }
        pq[++n] = x;
        MinHeapify_Swim(n);
    }

    void MinHeapify_Sink(int pos) {
        while (pos * 2 <= n) {
            int comp = pos * 2;
            if (comp < n && pq[comp] > pq[comp + 1]) {
                comp++;
            }
            if (pq[pos] <= pq[comp]) break;
            swap(pq[pos], pq[comp]);
            pos = comp;
        }
    }

    void MinHeapify_Swim(int pos) {
        while (pos > 1 && pq[pos / 2] > pq[pos]) {
            swap(pq[pos], pq[pos / 2]);
            pos = pos / 2;
        }
    }

    Key delMin() {
        if (n == 0) {
            throw std::runtime_error("Priority queue underflow");
        }
        swap(pq[1], pq[n]);
        Key minVal = pq[n--];
        MinHeapify_Sink(1);
        if (n > 0 && n <= capacity / 4) {
            resize(capacity / 2);
        }
        return minVal;
    }

    Key delRndm() {
        if (n == 0) {
            throw std::runtime_error("Priority queue underflow");
        }
        int rnd = rand() % n + 1;
        swap(pq[rnd], pq[n]);
        Key val = pq[n--];

        MinHeapify_Sink(rnd);
        MinHeapify_Swim(rnd);

        if (n > 0 && n <= capacity / 4) {
            resize(capacity / 2);
        }
        return val;
    }

    void Build_MinHeap() {
        for (int i = n / 2; i >= 1; i--) {
            MinHeapify_Sink(i);
        }
    }

    void Mn_Heapsort() {
        Build_MinHeap();
        int originalN = n;
        while (n > 1) {
            swap(pq[1], pq[n--]);
            MinHeapify_Sink(1);
        }
        n = originalN;
    }
};

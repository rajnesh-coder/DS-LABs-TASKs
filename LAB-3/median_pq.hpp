#pragma once
#include "maxpq_ra.hpp"
#include "minpq_ra.hpp"
using namespace std;

template <typename Key>
class DynamicMedian {
    Key v;
    bool hasMedian;
    MinPQ<Key> mn;
    MaxPQ<Key> mx;

public:
    DynamicMedian() : hasMedian(false), v() {}

    void insert(Key x) {
        if (!hasMedian) {
            v = x;
            hasMedian = true;
            return;
        }
        if (hasMedian && x < v) {
            mx.insert(x);
        } else if (hasMedian && x > v) {
            mn.insert(x);
        }

        if (mx.size() > mn.size()) {
            mn.insert(v);
            v = mx.delMax();
        } else if (mx.size() < mn.size()) {
            mx.insert(v);
            v = mn.delMin();
        }
    }

    Key median() {
        return v;
    }

    Key removeMedian() {
        if (mn.size() == mx.size()) {
            v = mx.delMax();
        } else if (mn.size() > mx.size()) {
            v = mn.delMin();
        }
        return v;
    }
};

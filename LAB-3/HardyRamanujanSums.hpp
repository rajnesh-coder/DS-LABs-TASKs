#pragma once
#include "maxpq_ra.hpp"
#include "minpq_ra.hpp"
using namespace std;

struct tupl{
    int a;
    int b;
    long long sum;
   bool operator<(const tupl& other) const { return sum < other.sum; }
    bool operator>(const tupl& other) const { return sum > other.sum; }
     bool operator==(const tupl& other) const { return sum == other.sum;}
      bool operator<=(const tupl& other) const { return sum <= other.sum;}
    };


class Sums {
    MinPQ<tupl> mn;
    int n;

public:
    Sums(int n_) : n(n_) {
        for (int i = 0; i <= n; i++) {
            tupl t = {i, i, (long long)i*i*i + (long long)i*i*i};
            mn.insert(t);
        }
    }

    tupl removeSmallest() {
        return mn.delMin();
    }

    void addNext(const tupl& t) {
        if (t.b < n) {
            tupl next = {t.a, t.b + 1, (long long)t.a*t.a*t.a + (long long)(t.b+1)*(t.b+1)*(t.b+1)};
            mn.insert(next);
        }
    }

    void genSums() {
        while (!mn.empty()) {
            tupl t = removeSmallest();
            cout << t.sum << " = " << t.a << "^3 + " << t.b << "^3\n";
            addNext(t);
        }
    }
    void HardyRamanujanSums(){
        tupl prev{-1,-1,-1};
        while(!mn.empty()){
            tupl t = removeSmallest();
            if(t.sum == prev.sum && (t.a != prev.a || t.b != prev.b)){
                   cout << t.sum << " = "
                     << prev.a << "^3 + " << prev.b << "^3 = "
                     << t.a << "^3 + " << t.b << "^3" << "\n" ;
            }
            prev = t;
            addNext(t);
        }
    }
};

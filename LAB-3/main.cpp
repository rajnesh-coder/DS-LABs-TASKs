#include <iostream>
#include "minpq_ra.hpp"
#include "maxpq_ra.hpp"
#include "median_pq.hpp"
#include "HardyRamanujanSums.hpp"
using namespace std;

int main() {
    cout << "================== Testing MinPQ ==================" << endl;
    MinPQ<int> minpq;
    minpq.insert(5);
    minpq.insert(2);
    minpq.insert(8);
    minpq.insert(1);
    minpq.insert(7);

    cout << "delMin sequence: ";
    while (!minpq.empty()) {
        cout << minpq.delMin() << " ";
    }
    cout << "\n";

    // refill
    minpq.insert(10);
    minpq.insert(3);
    minpq.insert(6);
    minpq.insert(4);

    cout << "delRndm: " << minpq.delRndm() << endl;
    cout << "Remaining after delRndm (delMin order): ";
    while (!minpq.empty()) cout << minpq.delMin() << " ";
    cout << "\n\n";


    cout << "================== Testing MaxPQ ==================" << endl;
    MaxPQ<int> maxpq;
    maxpq.insert(5);
    maxpq.insert(2);
    maxpq.insert(8);
    maxpq.insert(1);
    maxpq.insert(7);

    cout << "delMax sequence: ";
    while (!maxpq.empty()) {
        cout << maxpq.delMax() << " ";
    }
    cout << "\n";

    // refill
    maxpq.insert(10);
    maxpq.insert(3);
    maxpq.insert(6);
    maxpq.insert(4);

    cout << "delRndm: " << maxpq.delRndm() << endl;
    cout << "Remaining after delRndm (delMax order): ";
    while (!maxpq.empty()) cout << maxpq.delMax() << " ";
    cout << "\n\n";


    cout << "================== Testing DynamicMedian ==================" << endl;
    DynamicMedian<int> dm;
    int vals[] = {10, 5, 15, 3, 8, 12, 18};
    for (int x : vals) {
        dm.insert(x);
        cout << "Inserted " << x << ", current median = " << dm.median() << endl;
    }

    cout << "Removing medians: ";
    for (int i = 0; i < 3; i++) {
        cout << dm.removeMedian() << " ";
    }
    cout << "\n\n";


    cout << "================== Testing Sums (genSums) ==================" << endl;
    int n = 10,m = 50;
    Sums sums1(n);
    cout << "All sums up to n="<< n <<":" << endl;
    sums1.genSums();
    cout << "\n";

    cout << "================== Testing Hardy–Ramanujan Sums ==================" << endl;
    Sums sums2(50); // large enough to detect Hardy–Ramanujan
    sums2.HardyRamanujanSums();

    return 0;
}

#include <iostream>
#include <cmath>
#include <random>

class EggDrop {
public:
    EggDrop(int n) 
        : m(std::random_device()() % n + 1) {}

    bool operator()(int x) {
        return x >= m;
    }

private:
    int m;
};


int main() {
    int n = 10000;
    EggDrop eggdrop(n);
    
    int valK = 0;
   while(valK <n && !eggdrop(pow(2,valK))){
       valK++;
   }

    int lo = pow(2,valK-1), hi = pow(2,valK);
    
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (eggdrop(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    std::cout << "The value of m is " << lo << std::endl;
    return 0;
}

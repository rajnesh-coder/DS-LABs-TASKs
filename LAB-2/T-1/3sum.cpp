#include <vector>
#include <iostream>
#include <fstream>
#include "stopwatch.hpp"

using namespace std;

int count(const vector<int>& a) {
    int n = a.size();
    int c = 0;
    for (int i = 0; i < n; i++)   
        for (int j = i+1; j < n; j++)
            for (int k = j+1; k < n; k++)
                if (a[i] + a[j] + a[k] == 0)
                    c++;
    return c;
}

int main() {
    vector<int> sizes = {500, 1000, 2000, 4000, 8000, 16000};

    for (int n : sizes) {
        string fname = to_string(n) + "random.txt";
        ifstream in(fname);
        vector<int> a;
        int x;
        while (in >> x) a.push_back(x);
        in.close();

        Stopwatch timer;
        timer.reset();
        int res = count(a);
        double elapsed = timer.elapsedTime();

        cout << fname << " " << res << " " << elapsed << "s" << endl;
    }
}

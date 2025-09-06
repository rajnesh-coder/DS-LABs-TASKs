#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    for (int n = 500; n <= 16000; n *= 2) {
        string fname = to_string(n) + "random.txt";
        ofstream outFile(fname);

        if (outFile.is_open()) {
            for (int i = 0; i < n; i++) {
                int rnd = rand() % n + 1;
                outFile << rnd << "\n";
            }
        }

        outFile.close();
    }
}

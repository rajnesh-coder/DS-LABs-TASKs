#include "PercolationStat.hpp"
#include "stopwatch.hpp"
#include <iostream>
#include <fstream>

int main() {
    int n, trials;
    std::cout << "Enter grid size n: ";
    std::cin >> n;
    std::cout << "Enter number of trials: ";
    std::cin >> trials;

    std::ofstream fout("Comparison.txt");
    if (!fout) {
        std::cerr << "Error: could not open Comparison.txt for writing\n";
        return 1;
    }

    try {
      Stopwatch t;

        // Quick-Find
        t.reset();
        PercolationStats<Percolation_QF> statsQF(n, trials);
         double elapsedQF = t.elapsedTime();
        statsQF.report(fout, "Quick-Find");
        fout << "Execution time (QF): " << elapsedQF << " seconds\n\n";

        // Weighted Quick-Union
        t.reset();
        PercolationStats<Percolation_WQU>statsWQU (n, trials);
        double elapsedWQU = t.elapsedTime();
        statsWQU.report(fout, "Weighted Quick-Union");
        fout << "Execution time (WQU): " << elapsedWQU << " seconds\n\n";
        
        std::cout << "Comparison results written to Comparison.txt\n";
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

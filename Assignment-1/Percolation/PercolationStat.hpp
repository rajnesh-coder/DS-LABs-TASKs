#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Percolation_WQU.hpp"
#include "Percolation_QF.hpp"
template <typename PercolationType>
class PercolationStats {
    std::vector<double> thresholds;
    double cachedMean;
    PercolationType p;   // same object reused

public:
    PercolationStats(int n, int trials) 
        : cachedMean(0.0), p(n) {  
        if (n <= 0 || trials <= 0) {
            throw std::invalid_argument("n and trials must be > 0");
        }

        thresholds.reserve(trials);
        for (int i = 0; i < trials; i++) {
            int openCount = p.test();  
            double threshold = static_cast<double>(openCount) / (n * n);
            thresholds.push_back(threshold);
        }
    }

    double mean() {
        double sum = 0.0;
        for (double val : thresholds) sum += val;
        cachedMean = sum / thresholds.size();
        return cachedMean;
    }

    double stddev() {
        if (thresholds.size() <= 1) return 0.0;
        double m = mean();
        double sumSq = 0.0;
        for (double val : thresholds) sumSq += (val - m) * (val - m);
        return std::sqrt(sumSq / (thresholds.size() - 1));
    }

    double confidenceLow() {
        double s = stddev();
        return mean() - 1.96 * (s / std::sqrt(thresholds.size()));
    }

    double confidenceHigh() {
        double s = stddev();
        return mean() + 1.96 * (s / std::sqrt(thresholds.size()));
    }

    // Write results to file instead of cout
    template <typename Stream>
    void report(Stream &out, const std::string &label) {
        out << "=== " << label << " ===\n";
        out << "mean                    = " << mean() << '\n';
        out << "stddev                  = " << stddev() << '\n';
        out << "95% confidence interval = ["
            << confidenceLow() << ", " << confidenceHigh() << "]\n\n";
    }
};

#pragma once
#include "UnionFindAll.hpp"
#include <stdexcept>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>

class Percolation_WQU {
    int n;                                // grid size (n x n)
    int openSites;                        // count of open sites
    std::vector<std::vector<bool>> open;  // track open sites
    WQuickUnionUF uf;                     // union–find for connectivity
    int virtualTop;                       // virtual top node index
    int virtualBottom;                    // virtual bottom node index

    // flatten (row,col) into 1D index
    int index(int row, int col) const {
        return row * n + col;
    }

    bool valid(int row, int col) const {
        return row >= 0 && row < n && col >= 0 && col < n;
    }

public:
    // creates n-by-n grid, with all sites initially blocked
    Percolation_WQU(int n) : n(n), openSites(0), open(n, std::vector<bool>(n, false)), uf(n+2) {
        if (n <= 0) throw std::invalid_argument("Grid size must be > 0");
        int totalSites = n * n;
        virtualTop = totalSites;
        virtualBottom = totalSites + 1;
    }

    // is the site (row, col) open?
    bool isOpen(int row, int col) {
        if (!valid(row, col)) throw std::invalid_argument("Invalid index");
        return open[row][col];
    }

    // opens the site (row, col) if it is not open already
    void openSite(int row, int col) {
        if (!valid(row, col)) throw std::invalid_argument("Invalid index");
        if (open[row][col]) return;

        open[row][col] = true;
        openSites++;

        int site = index(row, col);

        // connect to virtual top/bottom if in first or last row
        if (row == 0) uf.unify({row,col}, {0,0}, n); // connect top row to virtualTop
        if (row == n-1) uf.unify({row,col}, {n-1,0}, n); // connect bottom row to virtualBottom

        // check neighbors
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};
        for (int k = 0; k < 4; k++) {
            int nr = row + dr[k], nc = col + dc[k];
            if (valid(nr, nc) && isOpen(nr, nc)) {
                uf.unify({row,col}, {nr,nc}, n);
            }
        }
    }

    // is the site (row, col) full? (connected to top)
    bool isFull(int row, int col) {
        if (!valid(row, col)) throw std::invalid_argument("Invalid index");
        if (!isOpen(row, col)) return false;

        int site = index(row, col);
        // check connectivity to any open site in top row
        for (int j = 0; j < n; j++) {
            if (isOpen(0, j) && uf.find({row,col}, n) == uf.find({0,j}, n)) {
                return true;
            }
        }
        return false;
    }

    // returns the number of open sites
    int numberOfOpenSites() {
        return openSites;
    }

    // does the system percolate?
    bool percolates() {
        for (int j = 0; j < n; j++) {
            if (isOpen(0, j)) {
                for (int i = 0; i < n; i++) {
                    if (isOpen(n-1, i)) {
                        if (uf.find({0,j}, n) == uf.find({n-1,i}, n)) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    // Monte Carlo test
    int test() {
        srand(time(0));
        Percolation_WQU p(n);
        int x, y;
        while (!p.percolates()) {
            x = rand() % n;
            y = rand() % n;
            p.openSite(x, y);
        }
        return p.numberOfOpenSites();
    }
};

#pragma once
#include <vector>
#include <utility>

class QuickFindUF {
    int n;
    std::vector<int> id;

public:
    QuickFindUF(int p) : n(p * p), id(p * p) {
        for (int i = 0; i < n; i++) id[i] = i;
    }

    int find(std::pair<int,int> pos, int dim) {
        return id[pos.first * dim + pos.second];
    }

    void unify(std::pair<int,int> a, std::pair<int,int> b, int dim) {
        int leaderA = find(a, dim);
        int leaderB = find(b, dim);
        if (leaderA == leaderB) return;

        for (int i = 0; i < n; i++) {
            if (id[i] == leaderA) id[i] = leaderB;
        }
    }
};

class QuickUnionUF {
    int n;
    std::vector<int> parent;

public:
    QuickUnionUF(int p) : n(p * p), parent(p * p) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int root(int i) {
        while (i != parent[i]) i = parent[i];
        return i;
    }

    int find(std::pair<int,int> pos, int dim) {
        return root(pos.first * dim + pos.second);
    }

    void unify(std::pair<int,int> a, std::pair<int,int> b, int dim) {
        int rootA = find(a, dim);
        int rootB = find(b, dim);
        if (rootA == rootB) return;
        parent[rootA] = rootB;
    }
};

class WQuickUnionUF {
    int n;
    std::vector<int> parent;
    std::vector<int> sz;

public:
    WQuickUnionUF() : n(0) {}
    WQuickUnionUF(int p) : n(p * p), parent(p * p), sz(p * p, 1) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int root(int i) {
        while (i != parent[i]) {
            parent[i] = parent[parent[i]]; // path compression
            i = parent[i];
        }
        return i;
    }

    int find(std::pair<int,int> pos, int dim) {
        return root(pos.first * dim + pos.second);
    }

    void unify(std::pair<int,int> a, std::pair<int,int> b, int dim) {
        int rootA = find(a, dim);
        int rootB = find(b, dim);
        if (rootA == rootB) return;

        if (sz[rootA] < sz[rootB]) {
            parent[rootA] = rootB;
            sz[rootB] += sz[rootA];
        } else {
            parent[rootB] = rootA;
            sz[rootA] += sz[rootB];
        }
    }
};

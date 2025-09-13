#include <bits/stdc++.h>
using namespace std;

// 2D Prefix Sums: Precompute O(R*C), answer rectangle sums in O(1).
template<class T>
struct PrefixSums {
    vector<vector<T>> sum; // (R+1)*(C+1)

    // Build prefix sums from a matrix of size R x C.
    void init(const vector<vector<T>> &v) {
        int R = int(v.size()), C = int(v[0].size());
        sum.assign(R + 1, vector<T>(C + 1, T{}));
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                sum[i + 1][j + 1] = v[i][j] + sum[i + 1][j] + sum[i][j + 1] - sum[i][j];
    }

    // Query sum over inclusive rectangle [X1..X2] x [Y1..Y2], 0-indexed
    T get(int X1, int X2, int Y1, int Y2) const {
        ++X2; ++Y2; // shift to 1-based for prefix table
        return sum[X2][Y2] - sum[X1][Y2] - sum[X2][Y1] + sum[X1][Y1];
    }
};
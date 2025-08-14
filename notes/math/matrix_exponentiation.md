## Usage
Matrix exponentiation is a tool to **speed up DP with constant space**.

**It can be used when we can combine two small values to form a larger one**. For example, in a directed graph, if we want to get the minimum cost path with exactly $X$ edges:
- We can easily say that the minimum cost of a path between two nodes $i$ and $j$ at distance $2 \cdot X$ is: the minimum cost across every path of length $X$ from $i$ to any node $k$ added with the minimum cost of any path from that node $k$ to the node $j$.
    - We can just minimize across every node $k$ to get the minimum cost from $i$ to $j$ with exactly $2 \cdot X$ edges.

## Matrix Multiplication
- Associative (not commutative)
- Distributive over addition (e.g., see problem https://codeforces.com/problemset/problem/718/C and https://usaco.guide/problems/cf-sasha-and-array/solution)

## Complexity
$\mathcal{O}(K^3 \cdot \log{N})$

## Code
Interesting note about efficiency: using arrays instead of vectors improves the efficiency $>5$ times.

```cpp
const int64_t MOD = int64_t(1e9) + 7;

const int SZ = 2;
typedef array<int64_t, SZ> vec;
typedef array<vec, SZ> MAT;

MAT zeros = MAT{vec{0, 0}, vec{0, 0}};
MAT iden = MAT{vec{1, 0}, vec{0, 1}};

MAT matadd(const MAT &a, const MAT &b) {
    MAT c = zeros;
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            c[i][j] = a[i][j] + b[i][j];
            if (c[i][j] >= MOD) c[i][j] -= MOD;
        }
    }
    return c;
}

MAT matmult(const MAT &a, const MAT &b) {
    MAT c = zeros;
    for (int i = 0; i < SZ; ++i) {
        for (int k = 0; k < SZ; ++k) {
            for (int j = 0; j < SZ; ++j) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= MOD;
            }
        }
    }
    return c;
}

MAT matexpo(MAT a, int64_t b) {
    MAT res = iden;
    while (b > 0) {
        if (b & 1) res = matmult(res, a);
        b >>= 1;
        a = matmult(a, a);
    }
    return res;
}
```
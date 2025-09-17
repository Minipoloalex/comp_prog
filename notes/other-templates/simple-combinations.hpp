#include <bits/stdc++.h>
using namespace std;

const int MAX = 20;
int64_t c[MAX+1][MAX+1];

void precompute() {
    memset(c, 0, sizeof(c));
    for (int i = 0; i <= MAX; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = c[i-1][j-1] + c[i-1][j];
        }
    }
}
int64_t comb(int n, int i) {
    return c[n][i];
}

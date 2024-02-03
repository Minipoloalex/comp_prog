#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 51;
typedef unsigned long long ul;

ul comb[MAX_N][MAX_N];

void compute_combinations() {
    for (int i = 0; i < MAX_N; i++) {
        comb[i][i] = 1;
        comb[i][0] = 1;
    }
    for (int r = 2; r < MAX_N; r++) {
        for (int c = 1; c < MAX_N - 1; c++) {
            comb[r][c] = comb[r - 1][c - 1] + comb[r - 1][c];
        }
    }
    // for (int i = 0; i < MAX_N; i++) {
    //     for (int j = 0; j < MAX_N; j++) {
    //         cout << comb[i][j] << " ";
    //     }
    //     cout << '\n';
    // }
}

bool is_probable_win(int n, int v1, int v2, int w) {
    ul combs = 0;
    ul votes_left = n - v1 - v2;
    for (int i = static_cast<int>(ceil((n + 1)* 1.0 / 2)); i <= n - v2; i++) {
        int bonus_votes_1 = i - v1;
        ul c = comb[votes_left][bonus_votes_1];
        // cout << "combs with votes " << i << ", bonus votes " << bonus_votes_1 << ": " << c << '\n';
        combs += c;
    }
    ul row_sum = ((ul) 1) << votes_left;
    // cout << "row_sum = " << row_sum << ", combs = " << combs << '\n';
    double prob = (double) combs / ((double) row_sum * 1.0);
    // cout << "prob: " << prob << ", w = " << w << '\n';
    return prob * 100 > w;
}

bool is_win(int n, int v) {
    return v >= n * 1.0 / 2;
}

int main() {
    compute_combinations();
    int t;
    cin >> t;
    while (t--) {
        int n, v1, v2, w;
        cin >> n >> v1 >> v2 >> w;
        if (is_win(n, v2)) {
            cout << "RECOUNT!" << '\n';
        }
        else if (is_win(n, v1) || is_probable_win(n, v1, v2, w)) {
            cout << "GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!" << '\n';
        }
        else {
            cout << "PATIENCE, EVERYONE!" << '\n';
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = int(1e9) + 7;

int pwr(int a, int b) {
    if (b == 0) return 1;
    int r = pwr(a, b / 2);
    if (b % 2 == 0) {
        return int((1LL * r * r) % MOD);
    }
    return int((1LL * r * r % MOD) * a % MOD);
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
    }
    for (int i = 0; i < n; i++) {
        int bi;
        cin >> bi;
        cout << pwr(2, bi) << '\n'; // Complexity: log(bi)
    }

    // // Checking that the 2^k solution is correct
    // vector<vector<int>> C(n, vector<int>(n, 0));
    // C[0][0] = 1;
    // for (int i = 1; i < n; i++) {
    //     C[i][0] = 1;
    //     C[i][i] = 1;
    //     for (int k = 1; k < n; k++) {
    //         cout << i << " " << k << endl;
    //         C.at(i).at(k) = (C.at(i).at(k - 1) + C.at(i - 1).at(k - 1)) % MOD;
    //     }
    // }
    // for (int i = 0; i < n; i++) {
    //     for (int k = 0; k <= i; k++) {
    //         cout << C[i][k] << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}

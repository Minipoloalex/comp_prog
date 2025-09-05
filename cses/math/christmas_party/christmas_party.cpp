#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;

void solve() {
    int n;
    cin >> n;
    vector<int64_t> derangements(n + 1);
    derangements[0] = 1;
    derangements[1] = 0;
    for (int i = 2; i <= n; i++) {
        derangements[i] = (i - 1) * (derangements[i - 2] + derangements[i - 1]) % MOD;
    }
    cout << derangements[n] << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

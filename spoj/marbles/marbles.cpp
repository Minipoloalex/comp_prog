#include <bits/stdc++.h>
using namespace std;

int64_t comb(int64_t n, int64_t k) {
    if (n - k < k) k = n - k;
    int64_t ans = 1;
    for (int i = 0; i < k; i++) {
        // we know ans will be divisible by (i + 1)
        // that's because we've seen (i + 1) consecutive numbers until now
        // (so it must be divisible by (i + 1))
        // also, we can't do ans *= (n - i) / (i + 1) because (n - i) may not be divisible by (i + 1)
        ans = ans * (n - i) / (i + 1);
    }
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    cout << comb(n - 1, k - 1) << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

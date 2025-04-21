#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;

int64_t mod_pow(int a, int b, int m) {
    if (b == 0) return 1;
    if (b & 1) return (a * mod_pow(a, b - 1, m)) % m;
    int64_t aux = mod_pow(a, b / 2, m);
    return (aux * aux) % m;
}

void solve() {
    int n;
    cin >> n;
    // also solvable iteratively multiplying (since n is just 1e6)
    int64_t ans = mod_pow(2, n, MOD);
    cout << ans << '\n';
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

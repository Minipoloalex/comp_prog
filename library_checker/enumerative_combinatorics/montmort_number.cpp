#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, m;
    cin >> n >> m;
    int64_t ans = 1;    // how many ways are there to organize 0-sized permutations (that ...): 1
    for (int i = 1; i <= n; i++) {
        ans = ((ans * i) % m + m + (i % 2 == 0 ? 1: -1)) % m;
        cout << ans << " \n"[i == n];
    }
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

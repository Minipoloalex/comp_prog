#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> f(n);
    for (auto &fi: f) cin >> fi;
    vector<int> ans(n);
    int mn = f[0];
    int mx = f[0];
    ans[0] = 1;
    for (int i = 0; i < n; i++) {
        if (mx + k >= f[i] && mn - k <= f[i]) {
            ans[i] = 1;
            mx = max(mx, f[i]);
            mn = min(mn, f[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n -1];
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) { 
        solve();
    }
    return 0;
}

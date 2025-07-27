#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> b(n);
    for (auto &bi: b) cin >> bi;
    int mn = int(1e9);
    bool ans = true;
    for (int i = 0; i < n; i++) {
        if (b[i] >= mn * 2) {
            ans = false;
            break;
        }
        mn = min(mn, b[i]);
    }
    cout << (ans ? "YES" : "NO") << '\n';
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; i++) {
        int ai;
        cin >> ai;
        pref[i] = pref[i-1]^ai;
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        int ans = pref[b] ^ pref[a-1];
        cout << ans << '\n';
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

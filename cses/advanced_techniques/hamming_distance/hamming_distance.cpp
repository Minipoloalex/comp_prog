#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) {
        string s;
        cin >> s;
        bitset<30> bs(s);
        ai = (int)bs.to_ulong();
    }
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = min(ans, __builtin_popcount(a[i] ^ a[j]));
        }
    }
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

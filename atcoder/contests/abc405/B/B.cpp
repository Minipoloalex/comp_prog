#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    vector<int> cnt(m + 1, 0);
    int ans = 0;
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[a[i]]++ == 0) {
            c++;
        }
        if (c == m) {
            ans = n - i;
            break;
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

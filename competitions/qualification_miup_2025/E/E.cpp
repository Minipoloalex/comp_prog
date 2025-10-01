#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    sort(a.begin(), a.end());
    int ans = 0;
    int l = 0, r = n - 1;
    for (int i = 0; i < m; i++) {
        int prod_left = r - l + 1;
        int ppl_left = m - i;   // [i,m)
        if (prod_left <= 0) break;
        if (prod_left < ppl_left * 2) {
            ans = max(ans, a[r]);
            r--;
        }
        else {
            ans = max(ans, a[r] + a[l]);
            l++;
            r--;
        }
    }
    cout << ans << '\n';
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

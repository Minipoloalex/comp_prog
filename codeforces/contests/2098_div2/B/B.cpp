#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    sort(a.begin(), a.end());
    int nn = n - k;
    int mn;
    int mx;
    if (nn % 2 == 0) {
        mn = max(0, nn / 2 - 1);
        mx = min(n - 1, nn / 2 + k);
    }
    else {
        mn = max(0, nn / 2);
        mx = min(n - 1, nn / 2 + k);
    }
    int mnval = a[mn];
    int mxval = a[mx];
    int ans = mxval - mnval + 1;
    cout << ans << '\n';
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

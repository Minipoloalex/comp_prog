#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> a[i];
    }
    double min_s = 0, max_s = 0;
    int sm = accumulate(a.begin(), a.end(), 0);
    min_s = sm - 0.5 * n;
    max_s = sm + 0.49 * n;
    bool ans = true;
    if (max_s < 100) {
        ans = false;
    }
    if (min_s > 100) {
        ans = false;
    }
    if (!ans) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    sm -= a[0];
    double sm_for_mn = sm + (n - 1) * 0.49;
    double sub = max(100 - sm_for_mn, a[0] - 0.5) - a[0];

    double sm_for_mx = sm - (n - 1) * 0.5;
    double add = min(100 - sm_for_mx, a[0] + 0.49) - a[0];

    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        cout << s[i] << " " << max(0.0, a[i] + sub) << " " << min(100.0, a[i] + add) << '\n';
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

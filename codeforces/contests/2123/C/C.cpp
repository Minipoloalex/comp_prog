#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
        mp[a[i]] = i;
    }
    vector<int> sufmx(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        sufmx[i] = max(sufmx[i + 1], a[i]);
    }
    int prefmin = INT_MAX;
    string ans(n, '0');
    for (int i = 0; i <= n; i++) {
        int sufmax = sufmx[i];
        if (i == 0) {
            ans[mp[sufmax]] = '1';
        }
        else if (i == n) {
            ans[mp[prefmin]] = '1';
        }
        else {
            ans[mp[prefmin]] = '1';
            ans[mp[sufmax]] = '1';
        }
        if (i < n) {
            prefmin = min(prefmin, a[i]);
        }
    }
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> s(n), t(n);
    for (auto &si: s) cin >> si;
    for (auto &ti: t) cin >> ti;
    multiset<int> remt;
    for (int i = 0; i < n; i++) {
        int rem = t[i] % k;
        remt.insert(rem);
    }
    bool ans = true;
    for (int i = 0; i < n; i++) {
        int rem1 = s[i] % k;
        int rem2 = abs(rem1 - k);
        auto it = remt.find(rem1);
        if (it == remt.end()) {
            it = remt.find(rem2);
            if (it == remt.end()) {
                ans = false;
                break;
            }
        }
        remt.erase(it);
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

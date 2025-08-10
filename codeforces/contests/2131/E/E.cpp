#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    bool ans = a.back() == b.back();
    for (int i = n - 2; i >= 0 && ans; i--) {
        int desired = a[i] ^ b[i];
        if (desired == 0 || desired == b[i + 1] || desired == a[i + 1]) {

        }
        else {
            ans = false;
        }
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

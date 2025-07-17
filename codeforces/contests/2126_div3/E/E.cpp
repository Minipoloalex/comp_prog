#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n), s(n);
    for (auto &pi: p) cin >> pi;
    for (auto &si: s) cin >> si;
    bool ans = true;
    for (int i = 1; i < n; i++) {
        int prev = p[i - 1];
        int cur = p[i];
        if (prev % cur != 0) {
            ans = false;
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        int prev = s[i + 1];
        int cur = s[i];
        if (prev % cur != 0) {
            ans = false;
        }
    }
    if (p[n - 1] != s[0]) ans = false;
    int g = p[n - 1];
    for (int i = 0; i < n - 1; i++) {
        if (gcd(p[i], s[i + 1]) != g) {
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

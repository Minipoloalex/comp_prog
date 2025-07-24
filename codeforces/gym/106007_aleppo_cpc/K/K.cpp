#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int v = 0;
    for (int i = 0; i < x; i++) {
        v &= a[i];
    }
    for (int i = x; i < n; i++) {
        v |= a[i];
    }
    cout << v << '\n';
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    int ans = 0;
    auto handle = [&](int i) {
        int g = 0;
        for (int j = 0; j + i < n; j++) {
            g = gcd(g, abs(a[j] - a[j + i]));
        }
        if (g != 1) ans++;
    };
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            handle(i);
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

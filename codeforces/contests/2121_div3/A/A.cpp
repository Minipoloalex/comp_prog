#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    int mn = x[0];
    int mx = x[n - 1];
    int ans = min(abs(s - mn) + abs(mx - mn), abs(s - mx) + abs(mx - mn));
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

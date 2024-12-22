#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &a: x) cin >> a;
    int64_t ans = LLONG_MIN, curr = 0;
    for (int i = 0; i < n; i++) {
        if (curr < 0) curr = 0;
        curr += x[i];
        ans = max(ans, curr);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<array<int64_t,4>> piles(n);

    int64_t ans = 0;
    for (auto &[a,b,c,d]: piles) {
        cin >> a >> b >> c >> d;
        int64_t leaving_0s = max(int64_t(0), a - c);
        int64_t min_0s = min(a, c);
        int64_t leaving_1s = max(int64_t(0), b - d);
        ans += leaving_0s + leaving_1s + (leaving_1s > 0 ? min_0s : 0);
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

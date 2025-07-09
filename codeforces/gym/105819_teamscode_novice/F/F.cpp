#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int64_t,int64_t>> keys(m);
    for (auto &[r, c]: keys) cin >> r >> c;
    int64_t xop = 0, yop = 0;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        xop ^= (1LL << x);
        yop ^= (1LL << y);
    }
    for (auto &[r, c]: keys) {
        for (int i = 0; i < 61; i++) {
            int64_t xbit = xop & (1LL << i);
            int64_t ybit = yop & (1LL << i);
            if (xbit) {
                // could also do: r % 2^x = r & ((1 << x) - 1)
                r = xbit - (r % xbit + 1) + (r / xbit) * xbit;
            }
            if (ybit) {
                c = ybit - (c % ybit + 1) + (c / ybit) * ybit;
            }
        }
        cout << r << " " << c << '\n';
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int sz = min(n, 30);
    sort(a.rbegin(), a.rend());
    vector<int> vals; vals.reserve(sz);
    while (q--) {
        vals.clear();
        for (int i = 0; i < sz; i++) {
            vals.push_back(a[i]);
        }
        int c;
        cin >> c;
        int ans = 0;
        /*
        for a given bit b (from largest to smallest), there are 3 options when
        analyzing the 2 largest available spaces:
        - Y Y : both fit this bit (in this case ans = 0, since other bits after this one will all fit in 2nd max)
        - Y N : one fits, other does not (so we need to place )
        - N N : it's "easy" to see that when it doesn't fit anywhere, we can just minimize the added value to ans
        */
        for (int i = 29; i >= 0; i--) {
            int val = c & (1 << i);
            if (val) {
                int mx = 0;
                int idx = -1;
                for (int j = 0; j < sz; j++) {
                    if (vals[j] >= mx) {
                        idx = j;
                        mx = vals[j];
                    }
                }
                assert(idx != -1);
                int v = mx;
                if (v < val) {
                    // doesn't fit anywhere: choose from any
                    ans += val - v;
                }
                vals[idx] = max(0, v - val);
            }
        }
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

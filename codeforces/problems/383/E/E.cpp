#include <bits/stdc++.h>
using namespace std;

const int LOG = 24;
int sos[1 << LOG];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int v = 0;
        for (int j = 0; j < 3; j++) {
            v |= (1 << (s[j] - 'a'));
        }
        sos[v]++;
    }
    for (int i = 0; i < LOG; i++) {
        for (int mask = 0; mask < (1 << LOG); mask++) {
            if (mask & (1 << i)) {
                sos[mask] += sos[mask ^ (1 << i)];
            }
        }
    }
    int full = (1 << LOG) - 1;
    int64_t ans = 0;
    for (int mask = 0; mask < (1 << LOG); mask++) {
        int inv = ~mask & full;
        int nr_submasks = sos[inv];
        int res = n - nr_submasks;
        ans ^= res*res;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

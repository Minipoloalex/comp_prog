#include <bits/stdc++.h>
using namespace std;

bool valid[1 << 17];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int planet_mask = 0;
        for (char c: s) {
            planet_mask |= (1 << (c - 'a'));
        }
        valid[planet_mask] = true;
    }
    for (int m=1; m<(1<<17); ++m) { // don't care about empty mask
        for (int s=m; s; s=(s-1)&m) {
            valid[m] |= valid[s];
        }
    }
    string s;
    cin >> s;
    int m = int(s.size());

    vector<array<int,17>> cnts(m, array<int,17>{});
    for (int i = 0; i < m; i++) {
        if (i > 0) cnts[i] = cnts[i - 1];
        int idx = s[i] - 'a';
        cnts[i][idx]++;
    }
    auto possible = [&](int i, int j) {
        array<int,17> cnt = cnts[j];
        if (i > 0) {
            for (int c = 0; c < 17; c++) {
                cnt[c] -= cnts[i-1][c];
            }
        }
        int mask = 0;
        for (int c = 0; c < 17; c++) {
            if (cnt[c]) mask |= (1 << c);
        }
        return valid[mask];
    };
    int64_t ans = 0;
    for (int i = 0; i < m; i++) {
        int lo = 0, hi = i;
        while (lo < hi) {
            int med = lo + (hi - lo + 1) / 2;
            if (possible(med, i)) {
                lo = med;
            }
            else {
                hi = med - 1;
            }
        }
        if (possible(lo, i)) {
            ans += lo + 1;
        }
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

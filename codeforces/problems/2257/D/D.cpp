#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t s;
    int q;
    cin >> s >> q;
    vector<int64_t> divs;
    for (int i = 1; 1LL * i * i <= s; i++) {
        if (s % i == 0) {
            divs.push_back(i);
            if (s / i != i) {
                divs.push_back(s / i);
            }
        }
    }
    sort(divs.begin(), divs.end());
    vector<int64_t> p(divs.size());
    p[0] = s;
    for (int i = 1; i < int(divs.size()); i++) {
        p[i] = p[i-1];
        p[i] += (divs[i] - divs[i-1]) * (s / divs[i]);
    }
    while (q--) {
        int64_t x, y;
        cin >> x >> y;
        int64_t ans = 0;
        int df = int(upper_bound(divs.begin(), divs.end(), s / y) - divs.begin()) - 1;
        int ds = int(upper_bound(divs.begin(), divs.end(), x) - divs.begin()) - 1;
        df = min(df, ds);
        ans += divs[df] * y;
        ans += p[ds] - p[df];

        int dn = ds + 1;
        if (dn < int(divs.size())) {
            int64_t rem = x - divs[ds];
            ans += rem * min(y, s / divs[dn]);
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

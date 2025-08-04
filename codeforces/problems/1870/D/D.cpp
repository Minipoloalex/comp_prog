#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> c(n);
    for (auto &ci: c) cin >> ci;
    vector<pair<int,int>> s;  // a stack
    for (int i = 0; i < n; i++) {
        while (!s.empty() && s.back().first >= c[i]) s.pop_back();
        s.emplace_back(c[i], i);
    }
    int k;
    cin >> k;
    vector<int> coef(s.size());
    int mx = k / s.front().first;
    coef[0] = mx;
    int64_t remainder = k - coef[0] * s.front().first;
    for (int i = 1; i < int(s.size()); i++) {
        auto possible = [&](int64_t med) {
            int64_t would_be_remainder = remainder + med * s[i - 1].first - med * s[i].first;
            return would_be_remainder;
        };
        int lo = 0, hi = coef[i - 1];
        while (lo < hi) {
            int med = lo + (hi - lo + 1) / 2;
            if (possible(med) >= 0) {
                lo = med;
            }
            else {
                hi = med - 1;
            }
        }
        if (lo == 0) {
            break;
        }
        remainder = possible(lo);
        coef[i - 1] -= lo;
        coef[i] = lo;
    }
    vector<int> ans(n);
    for (int i = 0; i < int(coef.size()); i++) {
        int origidx = s[i].second;
        ans[0] += coef[i];
        if (origidx + 1 < n) ans[origidx + 1] -= coef[i];
    }
    for (int i = 1; i < n; i++) {
        ans[i] += ans[i - 1];
    }
    for (int v: ans) cout << v << " ";
    cout << '\n';
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, p, q;
    cin >> n >> k >> p >> q;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    vector<int> s(n), bs(n), best(n);   // small, big -> small, best
    for (int i = 0; i < n; i++) {
        s[i] = a[i] % p;
        bs[i] = (a[i] % q) % p;
        best[i] = min(s[i], bs[i]);
    }
    auto compute_pref = [&](vector<int> &vec) {
        vector<int64_t> pf(n+1);
        for (int i = 0; i < n; i++) {
            pf[i+1] = pf[i] + vec[i];
        }
        return pf;
    };
    auto get_sum = [&](vector<int64_t> &pref, int i, int j) { // [i, j)
        return pref[j] - pref[i];
    };
    // could implement without prefix sums by keeping a value for each type
    vector<int64_t> pfbest = compute_pref(best);
    vector<int64_t> pfs = compute_pref(s);
    vector<int64_t> pfbs = compute_pref(bs);
    int64_t ans = INT64_MAX;
    for (int i = 0; i + k <= n; i++) {
        int64_t applys = get_sum(pfs, i, i+k);
        int64_t applybs = get_sum(pfbs, i, i+k);

        int64_t cur = pfbest[n] - get_sum(pfbest, i, i+k) + min(applys, applybs);
        ans = min(ans, cur);
    }
    cout << ans << '\n';
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

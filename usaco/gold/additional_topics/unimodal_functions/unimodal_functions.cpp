#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    sort(x.begin(), x.end());
    vector<int64_t> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + x[i];
    }
    vector<int> uni = {0};
    for (int i = 1; i < n; i++) {
        if (x[uni.back()] != x[i]) uni.push_back(i);
    }
    auto value = [&](int idx, int a, int b) {
        int xidx = uni[idx];
        int64_t y = x[xidx];
        int64_t cntbefore = xidx;
        int64_t cntafter = n - cntbefore;
        int64_t smbefore = pref[cntbefore];
        int64_t smafter = pref[n] - smbefore;
        int64_t ans = ((cntbefore * y) - smbefore) * a + (smafter - (cntafter * y)) * b;
        return ans;
    };
    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        int lo = 0, hi = int(uni.size() - 1);
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            if (value(m, a, b) < value(m + 1, a, b)) {
                hi = m;
            }
            else {
                lo = m + 1;
            }
        }
        cout << value(lo, a, b) << '\n';
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

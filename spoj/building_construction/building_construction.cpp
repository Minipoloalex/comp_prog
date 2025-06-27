#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> h(n);
    for (auto &hi: h) cin >> hi.first;
    for (auto &hi: h) cin >> hi.second;
    sort(h.begin(), h.end());
    // see in.txt for why we need unique values
    // we can't make a local decision if we don't have different values
    vector<int> uni = {0};
    for (int i = 1; i < n; i++) {
        if (h[uni.back()].first != h[i].first) uni.push_back(i);
    }
    auto value = [&](int uniidx) {
        int idx = uni[uniidx];
        int k = h[idx].first;
        int64_t ans = 0;
        for (int i = 0; i < n; i++) {
            ans += abs(h[i].first - k) * int64_t(h[i].second);
        }
        return ans;
    };
    int lo = 0, hi = int(uni.size() - 1);
    while (lo < hi) {
        int m = lo + (hi - lo) / 2;
        if (value(m) < value(m + 1)) {
            hi = m;
        }
        else {
            lo = m + 1;
        }
    }
    cout << value(lo) << '\n';
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

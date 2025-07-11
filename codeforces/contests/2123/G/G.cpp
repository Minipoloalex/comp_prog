#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int64_t> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> div;
    for (int i = 1; i * i <= m; i++) {
        if (m % i == 0) {
            div.push_back(i);
            if (m / i != i) div.push_back(m / i);
        }
    }
    sort(div.begin(), div.end());
    vector<vector<int64_t>> diffs;
    vector<int64_t> diffs_sum;
    for (int d = 0; d < int(div.size()); d++) {
        int64_t g = div[d];
        vector<int64_t> diff(n, 0);
        // a is 1-indexed, with a[0] = 0
        for (int i = 1; i <= n; i++) {
            diff[i-1] = ((a[i] - a[i-1]) % g + g) % g;
        }
        diffs.emplace_back(diff);
        diffs_sum.emplace_back(accumulate(diff.begin(), diff.end(), 0LL));
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;  // 1-indexed
            a[i] = x;
            for (int d = 0; d < int(div.size()); d++) {
                int64_t g = div[d];
                int64_t d1 = ((a[i] - a[i - 1]) % g + g) % g;
                int64_t prev1 = diffs[d][i-1];
                diffs[d][i-1] = d1;
                diffs_sum[d] += (d1 - prev1);
                if (i + 1 <= n) {
                    int64_t d2 = ((a[i + 1] - a[i]) % g + g) % g;
                    int64_t prev2 = diffs[d][i];
                    diffs[d][i] = d2;
                    diffs_sum[d] += (d2 - prev2);
                }
            }
        }
        else {
            assert(t == 2);
            int k;
            cin >> k;
            int g = gcd(k, m);
            // find g inside div
            int idx = int(lower_bound(div.begin(), div.end(), g) - div.begin());
            assert(idx < int(div.size()));
            int64_t total_diff = diffs_sum[idx];
            if (total_diff < m) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }
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

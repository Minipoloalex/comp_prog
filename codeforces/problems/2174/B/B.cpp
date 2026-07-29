#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

void solve() {
    int n, K;
    cin >> n >> K; // capital letter prevents classical mistake in using k instead of ki
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    vector<int> ids; ids.reserve(n);
    vector<pair<int,int>> ivals; ivals.reserve(n);
    int pfmx = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > pfmx) {
            ids.push_back(i);
            ivals.emplace_back(pfmx+1, a[i]+1); // [inclusive, exclusive)
            pfmx = a[i];
        }
    }
    ids.push_back(n);
    ivals.emplace_back(0, 0);
    int sz = int(ids.size());

    // could easily avoid one dimension
    vvvi dp(sz+1, vvi(K+1, vi(K+1, INT_MIN))); // id, k, mx
    dp[0][0][0] = 0;
    for (int i = 0; i < sz; i++) {
        for (int k = 0; k <= K; k++) {
            for (int mx = 0; mx <= K; mx++) {
                if (dp[i][k][mx] == INT_MIN) continue;
                int id = ids[i];
                int prvid = (i == 0) ? 0 : ids[i-1];
                dp[i+1][k][mx] = max(dp[i+1][k][mx], dp[i][k][mx] + mx * (id - prvid)); // make it 0

                // O(K) over the indices, so solution is 2 * k^3
                for (int j = ivals[i].first; j < ivals[i].second; j++) { // make it j (within the interval)
                    if (k + j <= K) {
                        dp[i+1][k+j][j] = max(dp[i+1][k+j][j], dp[i][k][mx] + mx * (id - prvid));
                    }
                }
            }
        }
    }
    int ans = 0;
    // keeping it precise and not propagating over k is easiest here, but requires this
    for (int k = 0; k <= K; k++) {
        for (int mx = 0; mx <= K; mx++) {
            ans = max(ans, dp[sz][k][mx]);
        }
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

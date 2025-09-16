#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;

void solve() {
    int k, L;
    cin >> k >> L;
    vector<vector<int>> mat(k, vector<int>(k));
    for (auto &vec: mat) for (auto &val: vec) cin >> val;
    int n;
    cin >> n;
    vector<int> p(n - 1);
    for (auto &pi: p) cin >> pi;
    auto find_interval = [&](int key, int val) {    // [l, r)
        auto &vec = mat[key];
        int l = int(lower_bound(vec.begin(), vec.end(), val - L) - vec.begin());
        int r = int(upper_bound(vec.begin(), vec.end(), val + L) - vec.begin());
        return make_pair(l, r);
    };
    vector<vector<int64_t>> dp(n + 1, vector<int64_t>(k, 0));
    vector<int64_t> prefsum;
    auto compute_pref = [&](int i) {
        prefsum.assign(k, 0);
        prefsum[0] = dp[i][0];
        for (int j = 1; j < k; j++) {
            prefsum[j] += prefsum[j - 1] + dp[i][j];
            prefsum[j] %= MOD;
        }
    };
    for (int j = 0; j < k; j++) {
        dp[n - 1][j] = 1;
    }
    compute_pref(n - 1);
    for (int i = n - 2; i >= 0; i--) {
        int tm = p[i];
        for (int j = 0; j < k; j++) {
            auto [l, r] = find_interval(j, tm);
            int64_t lval = l > 0 ? prefsum[l - 1] : 0;
            int64_t rval = r > 0 ? prefsum[r - 1] : 0;
            dp[i][j] = (rval - lval + MOD) % MOD;
        }
        compute_pref(i);
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < k; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cout << prefsum[k - 1] % MOD << '\n';
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

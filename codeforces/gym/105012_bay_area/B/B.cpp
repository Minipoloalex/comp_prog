#include <bits/stdc++.h>
using namespace std;

typedef vector<int64_t> vi;
typedef vector<vi> vvi;
typedef map<int,int> mii;

void check() {
    vvi dp(101, vi(101, -1));
    function<int64_t(int64_t,int64_t)> go = [&](int64_t cur, int64_t rem) -> int64_t {
        if (rem == 0) return 1;
        if (cur > 100) return 1;

        int64_t &ans = dp[cur][rem];
        if (ans != -1) return ans;

        int64_t curans = 1;
        for (int64_t use = 0; use * cur <= rem; use++) {
            int64_t used_sum = use * cur;
            curans = max(curans, (use + 1) * go(cur + 1, rem - used_sum));
        }
        return ans = curans;
    };
    cout << go(1, 100) << endl; // slightly bigger than 2e5 (i.e. 2e5 * 2 states for the DP below)
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n); for (auto &ai: a) cin >> ai;
    vector<int> b(m); for (auto &bi: b) cin >> bi;
    vector<int> pref(n);
    for (int i = 0; i < n; i++) {
        pref[i] = a[i];
        if (i > 0) {
            pref[i] += pref[i - 1];
        }
    }
    auto get_cost = [&](int all_to_one, int i, int j) {
        int ans = pref[j];
        if (i > 0) ans -= pref[i - 1];
        if (all_to_one) return j - i + 1 - ans;
        return ans; // all to zero: cost = nr of 1s
    };

    array<map<mii,int>,2> dp;
    function<int(mii&,int,int)> go = [&](mii &freq, int one, int i) {
        // we can recover index through frequency array, so i is deterministic
        if (i == n) return 0;

        if (dp[one].contains(freq)) {
            return dp[one][freq];
        }
        int cur_min = INT_MAX;
        for (auto &[v, f]: freq) {
            if (f > 0) {
                freq[v]--;
                cur_min = min(cur_min, get_cost(one, i, i + v - 1) + go(freq, 1 - one, i + v));
                freq[v]++;
            }
        }
        return dp[one][freq] = cur_min;
    };
    map<int,int> freq;
    for (int i = 0; i < m; i++) {
        freq[b[i]]++;
    }
    int min_cost = min(go(freq, 0, 0), go(freq, 1, 0));
    cout << min_cost << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    // check();
    while (t--) {
        solve();
    }
    return 0;
}

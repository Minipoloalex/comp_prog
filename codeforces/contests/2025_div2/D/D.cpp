#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> r(n);
    for (auto &ri: r) cin >> ri;
    vector<int> pending(m + 1, 0);
    vector<int> dp(m + 1, 0);
    int cnt0s = 0;
    for (int i = 0; i < n; i++) {
        if (r[i] == 0) {
            cnt0s++;
            for (int j = 1; j <= m; j++) {
                pending[j] += pending[j - 1];
            }
            for (int j = 0; j <= m; j++) {
                dp[j] += pending[j];
                pending[j] = 0;
            }
            for (int j = m; j >= 1; j--) {
                dp[j] = max(dp[j - 1], dp[j]);
            }
        }
        else if (r[i] > 0) {
            int fst = r[i];
            int lst = cnt0s;
            if (fst <= lst) {
                pending[r[i]]++;
                if (lst + 1 <= m) {
                    pending[lst + 1]--;
                }
            }
        }
        else {
            assert(r[i] < 0);
            int lst = cnt0s + r[i];
            if (lst >= 0) {
                pending[0]++;
                int after = lst + 1;
                if (after <= m) {
                    pending[after]--;
                }
            }
        }
    }
    for (int j = 1; j <= m; j++) {
        pending[j] += pending[j - 1];
    }
    for (int j = 0; j <= m; j++) {
        dp[j] += pending[j];
        pending[j] = 0;
    }
    for (int j = m; j >= 1; j--) {
        dp[j] = max(dp[j - 1], dp[j]);
    }
    int ans = *max_element(dp.begin(), dp.end());
    cout << ans << '\n';
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

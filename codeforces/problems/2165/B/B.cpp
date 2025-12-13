#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

void solve() {
    int n;
    cin >> n;
    vector<int> freq(n+1);
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        freq[ai]++;
    }
    vector<int> ord(n); iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [&freq](int a, int b) {
        return make_pair(freq[a], a) < make_pair(freq[b], b);
    });
    vector<vector<int64_t>> dp(n+1, vector<int64_t>(n+1,-1));
    function<int64_t(int,int)> go = [&](int i, int left) -> int64_t {
        if (i == n) return 1;
        int val = ord[i];

        int64_t &mem = dp[i][left];
        if (mem != -1) return mem;

        int64_t ans = 0;
        if (freq[val] <= left-freq[val]) {
            // freq[val] values are "hidden"
            ans += go(i+1,left-freq[val]);
        }
        for (int j = 1; j <= freq[val]; j++) {
            // can just stack them in one place (leaving open places for others to "hide")
            ans += go(i+1,left);
        }
        return mem = ans % MOD;
    };
    int64_t ans = go(0,n);
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

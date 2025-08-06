#include <bits/stdc++.h>
using namespace std;

typedef vector<int64_t> vi;
typedef vector<vi> vvi;

int vals[] = {1, 10, 100, 1000, 10000};
int get_idx(char c) {
    return c - 'A';
}

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());
    vector<vvi> dp(n, vvi(5, vi(2, -1)));
    function<int64_t(int,int,int)> go = [&](int i, int j, int k) -> int64_t {
        if (i == n) return 0;

        int64_t &ans = dp[i][j][k];
        if (ans != -1) return ans;

        int64_t mx = INT64_MIN;
        int curidx = get_idx(s[i]);

        int contrib = curidx < j ? -1 : 1;
        contrib *= vals[curidx];
        mx = max(mx, go(i + 1, max(j, curidx), k) + contrib);

        if (k == 0) {   // can replace it
            for (int replacement = 0; replacement < 5; replacement++) {
                int repl_contrib = replacement < j ? -1 : 1;
                repl_contrib *= vals[replacement];
                mx = max(mx, go(i + 1, max(j, replacement), 1) + repl_contrib);
            }
        }
        return ans = mx;
    };
    reverse(s.begin(), s.end());
    int64_t ans = go(0, 0, 0);
    cout << ans << '\n';
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

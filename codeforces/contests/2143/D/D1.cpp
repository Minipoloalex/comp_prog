#include <bits/stdc++.h>
using namespace std;

int64_t MOD = int64_t(1e9) + 7;
typedef vector<int64_t> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &ai: a) {
        cin >> ai; ai--;
    }
    vvvi dp(n, vvi(n, vi(n, -1)));
    function<int64_t(int,int,int)> go = [&](int i, int r, int b) -> int64_t {
        if (i == n) return 1;
        int64_t &mem = dp[i][r][b];
        if (mem != -1) return mem;

        int64_t ans = go(i+1,r,b);    // not included
        if (a[i] < r && a[i] >= b) {   // can't be red
            ans += go(i+1,r,a[i]);
        }
        else if (a[i] >= r && a[i] < b) { // can't be blue
            ans += go(i+1,a[i],b);
        }
        else if (a[i] >= r && a[i] >= b) {  // can be both
            // but we need to make sure not to overcount so:
            // greedy placement
            if (r < b) {
                ans += go(i+1,r,a[i]);
            }
            else {
                ans += go(i+1,a[i],b);
            }
        }
        ans %= MOD;
        return mem = ans;
    };
    int64_t ans = go(0,0,0);
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

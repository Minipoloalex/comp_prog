#include <bits/stdc++.h>
using namespace std;

const int MX = 60;
int64_t dp[MX+1][MX+1][MX+1];

int64_t go(int a, int b, int i) {
    if (a < 0 || b < 0) return INT64_MAX;
    if (a == 0 && b == 0) {
        return 0;
    }
    if (i == 0) return INT64_MAX;

    int64_t &mem = dp[a][b][i];
    if (mem != -1) return mem;

    int64_t ans = min(go(a-i,b,i-1),go(a,b-i,i-1));
    if (ans < INT64_MAX) ans += (1LL<<i);
    ans = min(ans, go(a,b,i-1));

    return mem = ans;
}

int sz(int64_t val) {
    for (int i = 0; ; i++) {
        if ((val >> i) == 0) {
            return i;
        }
    }
}

void solve() {
    int64_t x, y;
    cin >> x >> y;
    int xsz = sz(x);
    int ysz = sz(y);
    // cout << xsz << " " << ysz << endl;
    int64_t ans = INT64_MAX;
    for (int i = 0; i <= min(xsz, ysz); i++) {    // i: size of final number (in bits)
        // need to check that numbers are the same
        int64_t curx = x >> (xsz - i);
        int64_t cury = y >> (ysz - i);
        if (curx != cury) break;
        // cout << curx << " " << cury << endl;
        ans = min(ans,go(xsz-i,ysz-i,MX));
    }
    if (xsz == 2 && ysz == 2) {
        // the edge case doesn't exist for 1 bit, nor >= 3 bits
        // this is the only case where it's not possible to use different
        ans = min<int64_t>(ans, (1<<3) + (1<<2));
    }
    cout << ans << endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    memset(dp, -1, sizeof(dp));
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

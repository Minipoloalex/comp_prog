#include <bits/stdc++.h>
using namespace std;

#define sz(v) int(v.size())

int64_t dp[20][2][2][11];
string s;

int64_t go(int i, int below, int started, int prv) {
    if (i == sz(s)) return 1;

    int64_t &mem = dp[i][below][started][prv+1];
    if (mem != -1) return mem;

    int64_t cur = 0;
    int mx_digit = below ? 9 : s[i] - '0';
    for (int d = 0; d <= mx_digit; d++) {
        if (d == prv) continue;
        int nbelow = below ? true : d < mx_digit;
        int nstarted = started ? true : d > 0;
        int used_digit = nstarted ? d : prv;
        cur += go(i + 1, nbelow, nstarted, used_digit);
    }
    return mem = cur;
}

int64_t solve(int64_t nr) {
    s = to_string(nr);
    memset(dp, -1, sizeof(dp));
    return go(0, 0, 0, -1);
}

void solve() {
    int64_t a, b;
    cin >> a >> b;
    int64_t l = a == 0 ? 0 : solve(a - 1);
    int64_t r = solve(b);
    cout << r - l << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

vector<int> digits(int n) {
    vector<int> ans;
    while (n) {
        int d = n % 10;
        ans.push_back(d);
        n /= 10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int dp[10][2][2];

vector<int> dl, dr;
int n;
int go(int i, int above, int under) {
    if (i == n) return 0;

    int &ans = dp[i][above][under];
    if (ans != -1) return ans;

    int cur_best = INT_MAX;
    int mn = above ? 0 : dl[i];
    int mx = under ? 9 : dr[i];
    for (int d = mn; d <= mx; d++) {
        int nabove = above | (d > mn);
        int nunder = under | (d < mx);
        int nxt = (d == dl[i]) + (d == dr[i]) + go(i + 1, nabove, nunder);
        cur_best = min(cur_best, nxt);
    }
    ans = cur_best;
    return ans;
}

void solve() {
    int l, r;
    cin >> l >> r;
    dl = digits(l), dr = digits(r);
    n = int(dl.size());
    memset(dp, -1, sizeof(dp));
    int ans = go(0, 0, 0);
    cout << ans << endl;
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

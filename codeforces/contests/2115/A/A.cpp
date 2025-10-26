#include <bits/stdc++.h>
using namespace std;

const int inf = int(1e9);

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int g = 0;
    for (auto &ai: a) {
        cin >> ai;
        g = gcd(g, ai);
    }
    int ans = 0;
    bool easy = false;
    for (int i = 0; i < n; i++) {
        a[i] /= g;
        if (a[i] != 1) {
            ans++;
        }
        else {
            easy = true;
        }
    }
    if (!easy) {
        vector<vector<int>> dp(n, vector<int>(5001, -1));
        function<int(int,int)> go = [&](int i, int cur) {
            if (i == n) {
                if (cur == 1) return 0;
                return inf;
            }
            int &mem = dp[i][cur];
            if (mem != -1) return mem;

            int ncur = gcd(cur, a[i]);
            int mn = min(1 + go(i + 1, ncur), go(i + 1, cur));
            return mem = mn;
        };
        ans--;
        ans += go(0, 0) - 1;
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

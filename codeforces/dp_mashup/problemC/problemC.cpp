#include <bits/stdc++.h>
using namespace std;


int dp[1010][8];    // 8 possible values (2^3)

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> c(n), v(n, 0);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> c[i] >> s;

        for (char ch: s) {
            int amount = ch - 'A';
            v[i] |= 1 << amount;
        }
    }
    const int inf = int(1e9);

    memset(dp, -1, sizeof dp);
    auto func = [&](int i, int curr, auto &&self) -> int {
        if (curr == 0b111) return 0;
        if (i == n) return inf;

        int &ans = dp[i][curr];
        if (ans != -1) return ans;

        ans = min(c[i] + self(i + 1, curr | v[i], self), self(i + 1, curr, self));
        return ans;
    };
    int ans = func(0, 0, func);
    if (ans == inf) ans = -1;
    cout << ans << '\n';
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int MAX_X = int(1e5) + 10;

int dp[MAX_X];
const int inf = int(1e9);

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, x;
    cin >> n >> x;

    vector<int> hv(n), sv(n), kv(n);
    for (auto &a: hv) cin >> a;
    for (auto &a: sv) cin >> a;
    for (auto &a: kv) cin >> a;

    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) {
        int h = hv[i], s = sv[i], k = kv[i];
        for (int pwr = 1; k > 0; pwr <<= 1) {
            int cnt = min(k, pwr);
            k -= cnt;
            int nh = cnt * h;
            int ns = cnt * s;
            // cout << nh << " " << ns << endl;
            for (int j = x; j - nh >= 0; j--) {
                dp[j] = max(dp[j], dp[j - nh] + ns);
            }
            // for (int j = 0; j <= x; j++) {
            //     cout << dp[j] << " ";
            // }
            // cout << endl;
        }
    }
    int ans = 0;
    for (int i = 0; i <= x; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
    return 0;
}

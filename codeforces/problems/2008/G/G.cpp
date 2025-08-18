#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int64_t ans;
    if (n == 1) {
        if (a[0] < k) ans = k;
        else ans = k - 1;
    }
    else {
        int g = 0;
        for (int i = 0; i < n; i++) {
            g = gcd(g, a[i]);
        }
        ans = k - 1;
        for (int i = 0; i < n; i++) {
            int64_t v = i * g;
            if (v <= ans) {
                ans++;
            }
            else {
                break;
            }
        }
    }
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;

    int l = 0, r = 0;
    int64_t ans = 0;
    int cnt = 0;
    map<int,int> m;
    while (r < n) {
        while (cnt >= k && m[x[r]] == 0) {  // new number that does not fit within sliding window
            if (--m[x[l++]] == 0) {
                cnt--;   
            }
        }
        if (m[x[r++]]++ == 0) {
            cnt++;
        }

        // count subarrays ending at (r - 1)
        ans += (r - l);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    int ans = 0, curr = 0, curr_cnt = 0;
    for (int r = 0, l = 0; r < n; r++) {
        // include r
        curr += a[r];
        curr_cnt++;
        while (curr > t) {
            curr -= a[l++]; // exclude l
            curr_cnt--;
        }
        if (curr <= t) {
            ans = max(ans, curr_cnt);
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> have(k);
    int cnt_exactly = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < k) {
            have[a[i]] = 1;
        }
        if (a[i] == k) {
            cnt_exactly++;
        }
    }
    int cnt_not_have = 0;
    for (int i = 0; i < k; i++) {
        if (have[i] == 0) cnt_not_have++;
    }
    int ans = max(cnt_exactly, cnt_not_have);
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

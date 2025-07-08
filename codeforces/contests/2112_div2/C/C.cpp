#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &ai: arr) cin >> ai;
    int max_value = arr.back();
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int a = arr[i];
        for (int j = i + 1; j < n; j++) {
            int b = arr[j];
            int mn = max(max_value - (a + b), max(b - a, a - b));
            int mx = min(a + 1, min(b + 1, a + b));
            if (mx <= mn || mx - mn <= 1) {
                continue;
            }
            int cnt = int(upper_bound(arr.begin(), arr.begin() + i, mx - 1) - upper_bound(arr.begin(), arr.begin() + i, mn));
            ans += cnt;
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

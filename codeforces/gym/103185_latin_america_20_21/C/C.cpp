#include <bits/stdc++.h>
using namespace std;

int64_t solve(vector<int> a, int wanted) {
    int n = int(a.size());
    int cur = 0;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        cur += a[i];
        a[i] = min(wanted, cur);
        cur -= a[i];
        ans += cur;
    }
    for (int i = 0; i < n; i++) {
        cur -= wanted - a[i];
        ans += cur;
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int sum = accumulate(a.begin(), a.end(), 0);
    int wanted = sum / n;

    int64_t ans = solve(a, wanted);
    reverse(a.begin(), a.end());
    ans = min(ans, solve(a, wanted));
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

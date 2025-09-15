#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> l(n);
    for (auto &li: l) cin >> li;
    int ans = 2;
    for (int i = 0; i < n; i++) {
        if (l[i] == 1) {
            break;
        }
        else {
            ans++;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (l[i] == 1) {
            break;
        }
        else {
            ans++;
        }
    }
    ans = min(ans, n + 1);
    ans = n + 1 - ans;
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

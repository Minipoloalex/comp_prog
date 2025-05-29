#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    set<pair<int,int>, greater<pair<int,int>>> s;
    for (int i = 0; i < n; i++) {
        int pi;
        cin >> pi;
        s.emplace(pi, i);
    }
    int ans = 0;
    while (!s.empty()) {
        auto [pi, i] = *s.begin();
        s.erase({pi, i});
        auto otherit = s.lower_bound({x - pi, INT_MAX});
        if (otherit != s.end()) {
            s.erase(otherit);
        }
        ans++;
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

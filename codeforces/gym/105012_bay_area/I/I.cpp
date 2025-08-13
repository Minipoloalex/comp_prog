#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 2>> ans;
    set<array<int, 2>> seen;
    if (m & 1) {
        for (int i = 1; i <= n; i++) {
            ans.push_back({i, 1});
        }
        for (int i = 2; i <= m; i++) {
            ans.push_back({n, i});
        }
        for (int i = n - 1; i >= 1; i--) {
            ans.push_back({i, m});
        }

        for (int i = 3; i < m; i+=2) {
            for (int j = n - 1; j >= 1; j--) {
                ans.push_back({j, i});
            }
        }

        for (int i = 2; i < m; i+=2) {
            for (int j = n - 1; j >= 1; j--) {
                ans.push_back({j, i});
            }
        }

        for (auto& [f, s] : ans) {
            if (!seen.count({f, s})) cout << f << ' ' << s << '\n';
            seen.insert({f, s});
        }

    } else if (n & 1) {
        for (int i = 1; i <= m; i++) {
            ans.push_back({1, i});
        }
        for (int i = 2; i <= n; i++) {
            ans.push_back({i, m});
        }
        for (int i = m - 1; i >= 1; i--) {
            ans.push_back({n, i});
        }

        for (int i = 3; i < n; i+=2) {
            for (int j = m - 1; j >= 1; j--) {
                ans.push_back({i, j});
            }
        }

        for (int i = 2; i < n; i+=2) {
            for (int j = m - 1; j >= 1; j--) {
                ans.push_back({i, j});
            }
        }

        for (auto& [f, s] : ans) {
            if (!seen.count({f, s})) cout << f << ' ' << s << '\n';
            seen.insert({f, s});
        }
    }
    else {
        cout << -1 << '\n';
    }

    cout << '\n';
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

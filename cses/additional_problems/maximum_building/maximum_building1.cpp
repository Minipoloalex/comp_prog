#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> mp(n);
    for (auto &s: mp) cin >> s;
    
    // Basically the solution for CSES/advertisement after this preprocessing
    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            int after = j + 1 < m ? g[i][j + 1] : 0;
            if (mp[i][j] == '.') {
                g[i][j] = after + 1;
            }
            else {
                g[i][j] = 0;
            }
        }
    }
    auto get_max_col = [&](int j) {
        // this is another possible solution for CSES/advertisement
        // see problems.md
        int mx_area = 0;
        stack<ii> s;
        vector<int> col(n);
        for (int i = 0; i < n; i++) {
            col[i] = g[i][j];
        }
        col.push_back(0);
        for (int i = 0; i <= n; i++) {
            int val = col[i];
            int start = i;
            while (!s.empty() && val < s.top().second) {
                ii cur = s.top(); s.pop();
                start = cur.first;
                mx_area = max(mx_area, (i - start) * cur.second);   // [start, i)
            }
            s.emplace(start, val);
        }
        return mx_area;
    };
    int ans = 0;
    for (int j = 0; j < m; j++) {
        ans = max(ans, get_max_col(j));
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

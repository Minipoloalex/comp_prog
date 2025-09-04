#include <bits/stdc++.h>
using namespace std;

vector<int> divisors(int val) {
    vector<int> ans;
    for (int i = 1; 1LL * i * i <= val; i++) {
        if (val % i == 0) {
            ans.push_back(i);
            if (val / i != i) {
                ans.push_back(val / i);
            }
        }
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (auto &v: a) for (auto &val: v) cin >> val;

    vector<vector<int>> reach(n, vector<int>(m));
    auto possible = [&](int g) {
        reach.assign(n, vector<int>(m));
        reach[0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] % g == 0) {
                    if (i > 0) {
                        reach[i][j] |= reach[i - 1][j];
                    }
                    if (j > 0) {
                        reach[i][j] |= reach[i][j - 1];
                    }
                }
            }
        }
        return reach[n - 1][m - 1];
    };

    vector<int> divs = divisors(a[0][0]);
    int ans = 1;
    for (int divis: divs) {
        if (possible(divis)) {
            ans = max(ans, divis);
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

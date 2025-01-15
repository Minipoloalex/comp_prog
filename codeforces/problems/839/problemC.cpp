#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;

double dfs(int u, int p) {
    double ans = 0;
    int cnt = 0;
    for (int v: g[u]) {
        if (v != p) {
            cnt++;
            ans += dfs(v, u) + 1;
        }
    }
    if (cnt == 0) return 0;
    return ans / cnt;
}

void solve() {
    int n;
    cin >> n;
    g.assign(n, {});
    for (int i = 0; i < n - 1; i++) {
        int ui, vi;
        cin >> ui >> vi;
        ui--;vi--;
        g[ui].push_back(vi);
        g[vi].push_back(ui);
    }

    double ans = dfs(0, -1);
    cout << fixed << setprecision(16) << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

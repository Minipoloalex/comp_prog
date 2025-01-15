#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> g;

int dfs(int u, int p, int lmt) {
    int ans = 1;
    for (auto &[v, r]: g[u]) {
        if (v != p && r >= lmt) {
            ans += dfs(v, u, lmt);
        }
    }
    return ans;
}

void solve() {
    int n, q;
    cin >> n >> q;
    g.assign(n, {});
    for (int i = 0; i < n - 1; i++) {
        int pi, qi, ri;
        cin >> pi >> qi >> ri;
        pi--;qi--;
        g[pi].emplace_back(qi, ri);
        g[qi].emplace_back(pi, ri);
    }
    while (q--) {
        int ki, vi;
        cin >> ki >> vi;
        vi--;
        cout << dfs(vi, -1, ki) - 1 << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);
    solve();
    return 0;
}

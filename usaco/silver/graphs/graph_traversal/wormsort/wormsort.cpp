#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> g;
vector<int> vis;
vector<int> cows;
void dfs(int u, int lmt, vector<int> &cc_cows, vector<int> &cc_pos) {
    vis[u] = 1;
    cc_cows.push_back(cows[u]);
    cc_pos.push_back(u);
    for (auto &[v, w]: g[u]) {
        if (w >= lmt && !vis[v]) {
            dfs(v, lmt, cc_cows, cc_pos);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    cows.resize(n);
    for (auto &x: cows) {
        cin >> x;
        x--;
    }
    g.assign(n, {});
    while (m--) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        g[a].emplace_back(b, w);
        g[b].emplace_back(a, w);
    }

    auto possible = [&](int med) -> bool {
        vis.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;

            vector<int> cc_cows, cc_pos;
            dfs(i, med, cc_cows, cc_pos);

            sort(cc_cows.begin(), cc_cows.end());
            sort(cc_pos.begin(), cc_pos.end());

            if (cc_cows != cc_pos) return false;
        }
        return true;
    };
    const int MAX = int(1e9 + 1);
    int lo = 0, hi = MAX;
    while (lo < hi) {
        int med = lo + (hi - lo + 1) / 2;
        if (possible(med)) {
            lo = med;
        }
        else {
            hi = med - 1;
        }
    }
    if (lo == MAX) lo = -1;
    cout << lo << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    solve();
    return 0;
}

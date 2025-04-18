#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> pos(n);
    vector<int64_t> c(n), k(n);
    for (auto &[x, y]: pos) cin >> x >> y;

    for (auto &ci: c) cin >> ci;

    for (auto &ki: k) cin >> ki;

    auto weight = [&](int u, int v) {
        int64_t ks = k[u] + k[v];
        auto &[xu, yu] = pos[u];
        auto &[xv, yv] = pos[v];
        int64_t d = abs(xu - xv) + abs(yu - yv);
        return d * ks;
    };
    vector<int64_t> dist = c;
    vector<bool> vis(n, 0);
    vector<int> p(n, -1);
    set<pair<int64_t,int>> pq;
    for (int i = 0; i < n; i++) {
        pq.emplace(dist[i], i);
    }
    int64_t yen = 0;
    vector<pair<int,int>> edges;
    vector<int> pwr;
    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        vis[u] = 1;
        yen += d;
        if (p[u] == -1) {
            pwr.push_back(u);
        }
        else {
            edges.emplace_back(u, p[u]);
        }
        for (int v = 0; v < n; v++) {
            if (v == u || vis[v]) continue;
            int64_t cost = weight(u, v);
            if (cost < dist[v]) {
                auto it = pq.find({dist[v], v});
                pq.erase(it);
                dist[v] = cost;
                pq.emplace(dist[v], v);
                p[v] = u;
            }
        }
    }
    cout << yen << '\n';
    cout << pwr.size() << '\n';
    for (int pr: pwr) {
        cout << pr + 1 << " ";
    }
    cout << '\n';
    cout << edges.size() << '\n';
    for (auto &[u, v]: edges) {
        cout << u + 1 << " " << v + 1 << '\n';
    }
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

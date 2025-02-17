#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> g;
void dijkstra(int st, vector<int64_t> &dist) {
    dist[st] = 0;
    set<pair<int64_t, int>> pq;
    pq.emplace(dist[st], st);
    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        for (auto &[v, l]: g[u]) {
            if (dist[u] + l < dist[v]) {
                auto it = pq.find({dist[v], v});
                if (it != pq.end()) pq.erase(it);
                dist[v] = dist[u] + l;
                pq.emplace(dist[v], v);
            }
        }
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    g.resize(n);
    while (m--) {
        int i, j, l;
        cin >> i >> j >> l;
        i--;j--;
        g[i].emplace_back(j, l);
        g[j].emplace_back(i, l);
    }
    vector<int64_t> srcdist(n, INT64_MAX), dstdist(n, INT64_MAX);
    dijkstra(0, srcdist);
    dijkstra(n - 1, dstdist);

    vector<pair<int64_t, double>> paths(k);
    bool possible = false;
    for (int i = 0; i < k; i++) {
        int idx;
        double p;
        cin >> idx >> p;
        idx--;
        if (p == 1) possible = true;

        int64_t src = srcdist[idx];
        int64_t dst = dstdist[idx];
        int64_t path_dist = src + dst;
        paths[i] = make_pair(path_dist, p);
    }
    if (!possible) {
        cout << "impossible\n";
        return;
    }
    sort(paths.begin(), paths.end());
    double ans = 0;
    double prob_none_before = 1;
    for (auto &[d, p]: paths) {
        double xp = prob_none_before * p * double(d);
        ans += xp;
        prob_none_before *= (1 - p);
        if (p == 1) break;
    }
    cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

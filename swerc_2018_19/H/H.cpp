#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, e;
    cin >> n >> e;
    vector<vector<pair<int,int>>> g(n);
    while (e--) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].emplace_back(b, w);
        g[b].emplace_back(a, w);
    }
    const int inf = int(1e9);
    auto sp = [&](int src, vector<array<int,3>> &res) {
        set<pair<int,int>> pq;
        vector<int> dist(n, inf);
        dist[src] = 0;
        pq.emplace(0, src);
        while (!pq.empty()) {
            auto [d, u] = *pq.begin();
            pq.erase(pq.begin());
            for (auto &[v, w]: g[u]) {
                if (dist[u] + w < dist[v]) {
                    pq.erase({dist[v], v});
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            res[i][src] = dist[i];
        }
    };
    vector<array<int,3>> dists(n);
    for (int i = 0; i < 3; i++) {
        sp(i, dists);
    }
    sort(dists.begin(), dists.end());
    set<pair<int,int>> s;
    s.emplace(dists[0][1], 0);
    int ans = 1;
    for (int i = 1; i < n; ) {
        auto &[x, y, z] = dists[i];
        auto it_first_larger_or_equal = s.lower_bound({y, -1});
        auto it_first_larger = s.lower_bound({y, INT_MAX});
        bool should_insert = true;
        if (it_first_larger != s.begin()) {
            // check previous element's Z
            auto previous_it = prev(it_first_larger);
            auto &[y2, i2] = *previous_it;
            int z2 = dists[i2][2];
            if (z2 <= z) {
                should_insert = false;
            }
        }
        if (should_insert) {
            for (auto it = it_first_larger_or_equal; it != s.end(); ) {
                auto [y2, i2] = *it;
                int z2 = dists[i2][2];
                // y2 is worse, let's check if z2 is also worse
                if (z2 >= z) {
                    it = s.erase(it);
                }
                else break;
            }

            int j;
            for (j = i; j < n && dists[i] == dists[j]; j++) {
                ans++;
            }
            s.emplace(y, i);
            i = j;
        }
        else {
            i++;
        }
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

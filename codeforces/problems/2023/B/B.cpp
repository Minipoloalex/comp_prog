#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi, bi--;

    vector<int64_t> dist(n, INT64_MAX);
    dist[0] = 0;
    set<pair<int64_t,int>> pq;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [d, src] = *pq.begin();
        pq.erase(pq.begin());
        if (b[src] > src) {
            int dst = b[src];
            if (dist[src] + a[src] < dist[dst]) {
                pq.erase({dist[dst], dst});
                dist[dst] = dist[src] + a[src];
                pq.emplace(dist[dst], dst);
            }
        }
        if (src > 0 && dist[src] < dist[src - 1]) {
            int dst = src - 1;
            pq.erase({dist[dst], dst});
            dist[dst] = dist[src];
            pq.emplace(dist[dst], dst);
        }
    }
    // could have made an array pref, but this is simple
    int64_t pref = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        pref += a[i];
        ans = max(ans, pref - dist[i]);
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

#include <bits/stdc++.h>
using namespace std;

using iii = tuple<int64_t, int64_t, int64_t>;
using viii = vector<iii>;

using ii = pair<int64_t, int64_t>;
using vii = vector<ii>;

using vi64 = vector<int64_t>;
using vvi = vector<vi64>;

const int MAX_N = int(2e5) + 10;
vector<vii> el;
bitset<MAX_N> horse;

void dijkstra(int st, vvi &dist) {
    dist.at(st).at(0) = 0;

    set<iii> pq;
    pq.emplace(0, st, 0);

    // cerr << "Starting dijkstra: " << endl;
    while (!pq.empty()) {
        auto [d, u, currHorse] = *pq.begin();   // currHorse = 1 if already had a horse
        // cerr << u << " ";
        pq.erase(pq.begin());
        bool nhorse = currHorse || horse[u];    // nhorse = 1 if already had a horse or got a horse in this node

        for (auto [v, w]: el.at(u)) {
            if (nhorse) w /= 2; // w is a copy

            if (dist.at(u).at(currHorse) + w < dist.at(v).at(nhorse)) {
                pq.erase({dist[v][nhorse], v, nhorse}); // no problem if not in the set

                dist[v][nhorse] = dist[u][currHorse] + w;
                pq.emplace(dist[v][nhorse], v, nhorse);
            }
        }
    }
    // cerr << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, h;
        cin >> n >> m >> h;
        el.assign(n, vii());
        horse.reset();
        for (int i = 0; i < h; i++) {
            int ai;
            cin >> ai;
            horse.set(ai - 1);
        }
        for (int i = 0; i < m; i++) {
            int64_t ui, vi, wi;
            cin >> ui >> vi >> wi;
            ui--;vi--;
            el[ui].emplace_back(vi, wi);
            el[vi].emplace_back(ui, wi);
        }
        vvi distFrom1(n, vi64(2, INT64_MAX)), distFromN(n, vi64(2, INT64_MAX));

        dijkstra(0, distFrom1);
        dijkstra(n - 1, distFromN);

        // cerr << "Distance calculation: " << endl;
        int64_t ans = INT64_MAX;
        for (int i = 0; i < n; i++) {
            // cerr << i << " " << distFrom1[i][0] << " " << distFrom1[i][1] << " " << distFromN[i][0] << " " << distFromN[i][1] << endl;
            int64_t min_dist_1 = min(distFrom1[i][0], distFrom1[i][1]);
            int64_t min_dist_n = min(distFromN[i][0], distFromN[i][1]);
            int64_t actual = max(min_dist_1, min_dist_n);
            ans = min(ans, actual);
        }
        if (ans == INT64_MAX) ans = -1;
        cout << ans << '\n';
    }
    return 0;
}

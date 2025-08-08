#include <bits/stdc++.h>
using namespace std;

int distance(pair<int,int> &src, pair<int,int> &dst) {
    auto &[xa, ya] = src;
    auto &[xb, yb] = dst;
    int dx = xa - xb;
    int dy = ya - yb;
    return int(ceil(sqrt(dx * dx + dy * dy)));
}

int compute_cost(int time_wasted, int cost) {
    return time_wasted * cost;
}

void solve() {
    int xs, ys, xd, yd, b, c0, t, n;
    cin >> xs >> ys;
    cin >> xd >> yd;
    cin >> b;
    cin >> c0;
    cin >> t;
    vector<int> transportcosts(t + 1);
    transportcosts[0] = c0;
    for (int i = 1; i <= t; i++) cin >> transportcosts[i];
    cin >> n;
    vector<vector<pair<int,int>>> g(n + 2);
    vector<pair<int,int>> stations(n + 2);
    stations[0] = {xs, ys};
    stations[n + 1] = {xd, yd};
    g[0].emplace_back(n + 1, 0);
    for (int station = 1; station <= n; station++) {
        g[0].emplace_back(station, 0);
        g[station].emplace_back(n + 1, 0);

        auto &[x, y] = stations[station];
        cin >> x >> y;
        int li;
        cin >> li;
        for (int i = 0; i < li; i++) {
            int j, mj;
            cin >> j >> mj;
            j++;
            g[station].emplace_back(j, mj);
            g[j].emplace_back(station, mj);
        }
    }
    vector<vector<int>> dist(n + 2, vector<int>(b + 1, INT_MAX));
    dist[0][0] = 0;
    set<array<int,3>> pq;
    pq.insert({0, 0, 0});
    while (!pq.empty()) {
        auto [curcost, curtime, station] = *pq.begin();
        pq.erase(pq.begin());
        for (auto &[destination, transport]: g[station]) {
            int time_to_traverse = distance(stations[station], stations[destination]);
            int cost_to_traverse = compute_cost(time_to_traverse, transportcosts[transport]);
            int nxt_time = curtime + time_to_traverse;
            int nxt_cost = curcost + cost_to_traverse;
            if (nxt_time <= b && nxt_cost < dist[destination][nxt_time]) {
                pq.erase({dist[destination][nxt_time], nxt_time, destination});
                dist[destination][nxt_time] = nxt_cost;
                pq.insert({nxt_cost, nxt_time, destination});
            }
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i <= b; i++) {
        // cout << dist[n + 1][i] << " ";
        ans = min(ans, dist[n + 1][i]);
    }
    // cout << endl;
    if (ans == INT_MAX) ans = -1;
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

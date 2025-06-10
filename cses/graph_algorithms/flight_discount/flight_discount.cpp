#include <bits/stdc++.h>
using namespace std;

const int64_t INF = int64_t(1e18);  // could also be 1e18

// // This won't work: needs dijksta-like implementation
// vector<array<int64_t,2>> dp(n, {-1,-1});
// // we can assume it is possible to get from 0 to n - 1
// function<int64_t(int, int)> go = [&](int u, int used) -> int64_t {
//     if (u == n - 1) {
//         return 0;
//     }
//     int64_t &ans = dp[u][used];
//     if (ans != -1) return ans;

//     dp[u][used] = INF;
//     for (auto &[v, w]: g[u]) {
//         dp[u][used] = min(dp[u][used], go(v, used) + w);
//         if (!used) {
//             dp[u][used] = min(dp[u][used], go(v, 1) + w / 2);
//         }
//     }
//     return dp[u][used];
// };
// go(0, 0);
// cout << dp[0][0] << '\n';


// Modified Dijkstra with additional parameters (which are exponential so need to be small)
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int64_t>>> g(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a-1].emplace_back(b-1,c);
    }
    vector<array<int64_t,2>> d(n, {INF, INF});
    set<tuple<int64_t,int,int>> pq;
    d[0][0] = d[0][1] = 0;  // we always have 2 nodes, so d[0][1] = 0 is not necessary
    pq.emplace(0, 0, 0);
    while (!pq.empty()) {
        auto [dist, u, used] = *pq.begin();
        pq.erase(pq.begin());
        for (auto &[v, w]: g[u]) {
            if (d[u][used] + w < d[v][used]) {
                pq.erase({d[v][used], v, used});
                d[v][used] = d[u][used] + w;
                pq.emplace(d[v][used], v, used);
            }
            if (!used && d[u][0] + w / 2 < d[v][1]) {
                pq.erase({d[v][1], v, 1});
                d[v][1] = d[u][0] + w / 2;
                pq.emplace(d[v][1], v, 1);
            }
        }
    }
    cout << d[n-1][1] << '\n';
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

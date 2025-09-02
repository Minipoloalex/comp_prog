#include <bits/stdc++.h>
using namespace std;

typedef array<int,3> E;

class top_order {
public:
    int n; vector<vector<E>> g;

    top_order(vector<vector<E>>& A) : n(int(A.size())), g(A) {}

    vector<int> sort() {
        vector<int> indeg(n, 0), res;
        for (auto& l : g) for (auto& [x,_,__] : l) indeg[x]++;
        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            res.push_back(u);
            for (auto& [x,_,__] : g[u]) {
                if (--indeg[x] == 0) q.push(x);
            }
        }
        return res; // make sure res.size() == n
    }
};

typedef pair<int,int> ii;
const int MAX_R = int(1e4);

ii comb(ii const&a, int cost, int prestige) {
    return {a.first + cost, a.second + prestige};
}
ii best_fn(ii &a, ii &b) {
    return a.first < b.first || (a.first == b.first && a.second > b.second) ? a : b;
}

void solve() {
    int b, n;
    cin >> b >> n;
    map<string,int> mp;
    vector<vector<E>> g(MAX_R);
    int id = 0;
    for (int i = 0; i < n; i++) {
        string from, to, ing;
        int cost, prestige;
        cin >> to >> from >> ing >> cost >> prestige;
        int toid, fromid;
        if (mp.contains(from)) {
            fromid = mp[from];
        }
        else {
            fromid = id++;
            mp[from] = fromid;
        }
        if (mp.contains(to)) {
            toid = mp[to];
        }
        else {
            toid = id++;
            mp[to] = toid;
        }
        g[fromid].push_back({toid, cost, prestige});
    }

    n = id;
    g.resize(n);
    top_order top(g);
    vector<int> order = top.sort();
    const ii def = {INT_MAX, INT_MIN}, base = {0, 0};
    vector<ii> best(n, def);
    for (int i = 0; i < n; i++) {
        int u = order[i];
        if (best[u] == def) best[u] = base;
        for (auto &[v, cost, prestige]: g[u]) {
            ii new_best_v = comb(best[u], cost, prestige);
            best[v] = best_fn(best[v], new_best_v);
        }
    }

    best.insert(best.begin(), {-1,-1});
    vector<vector<int>> dp(n + 1, vector<int>(b + 1));
    for (int i = 1; i <= n; i++) {
        auto &[ci, pi] = best[i];
        for (int k = 1; k <= b; k++) {
            dp[i][k] = dp[i - 1][k];
            if (k >= ci) {
                dp[i][k] = max(dp[i][k], pi + dp[i - 1][k - ci]);
            }
        }
    }
    int mx = INT_MIN;
    int cost = INT_MAX;
    for (int k = 0; k <= b; k++) {
        if (dp[n][k] > mx) {
            mx = dp[n][k];
            cost = k;
        }
    }
    cout << mx << '\n' << cost << '\n';
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

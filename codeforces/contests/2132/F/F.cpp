#include <bits/stdc++.h>
using namespace std;

int n, m;   // number of nodes

vector<int> spedges;
vector<int> useful;

// some function to process the found bridge
void IS_BRIDGE(int idx) {
    auto it = lower_bound(spedges.begin(), spedges.end(), idx);
    if (it != spedges.end() && *it == idx) {
        useful.push_back(idx);
    }
};

vector<vector<pair<int,int>>> adj; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;
    for (auto &[to, idx] : adj[v]) {
        if (to == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                IS_BRIDGE(idx);
        }
    }
}

void find_bridges() {
    useful.clear();
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

vector<pair<int,int>> edges;
vector<int> source_edges;
void bfs(vector<pair<int,int>> const&srcs, bool find_spedges) {
    source_edges.assign(n, -1);
    queue<int> q;
    vector<int> vis(n), par(n, -1);
    for (pair<int,int> const&s: srcs) {
        q.push(s.second);
        vis[s.second] = 1;
        if (source_edges[s.second] == -1) {
            source_edges[s.second] = s.first;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &[v, idx]: adj[u]) {
            if (!vis[v]) {
                source_edges[v] = source_edges[u];
                vis[v] = 1;
                par[v] = idx;
                q.push(v);
            }
        }
    }
    if (find_spedges) {
        int cur = n - 1;
        spedges.clear();
        while (cur != 0) {
            int eidx = par[cur];
            auto &[u, v] = edges[eidx];
            spedges.push_back(eidx);

            if (u == cur) cur = v;
            else cur = u;
        }
        sort(spedges.begin(), spedges.end());
    }
}

void solve() {
    cin >> n >> m;
    adj.clear();
    adj.resize(n);
    edges.clear();
    edges.resize(m);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
        edges[i] = {u, v};
    }

    bfs({{-1, 0}}, true);
    find_bridges();

    vector<pair<int,int>> srcs;
    for (int idx: useful) {
        auto &[u, v] = edges[idx];
        srcs.emplace_back(idx, u);
        srcs.emplace_back(idx, v);  // duplicate nodes don't matter in srcs  
    }
    sort(srcs.begin(), srcs.end()); // give priority to smaller indices

    bfs(srcs, false);

    int Q;
    cin >> Q;
    while (Q--) {
        int c;
        cin >> c;
        c--;
        if (useful.empty()) {
            cout << "-1 ";
        }
        else {
            cout << source_edges[c] + 1 << " ";
        }
    }
    cout << '\n';
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

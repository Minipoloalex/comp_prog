#include <bits/stdc++.h>
using namespace std;
vector<bool> visited; // keeps track of which vertices are already visited

// runs depth first search starting at vertex v.
// each visited vertex is appended to the output vector when dfs leaves it.
void dfs(int v, vector<vector<int>> const& adj, vector<int> &output) {
    visited[v] = true;
    for (auto u : adj[v])
        if (!visited[u])
            dfs(u, adj, output);
    output.push_back(v);
}

// input: adj -- adjacency list of G
// output: components -- the strongy connected components in G
// output: adj_cond -- adjacency list of G^SCC (by root vertices)
void strongly_connected_components(vector<vector<int>> const& adj,vector<vector<int>> &components,vector<vector<int>> &adj_cond) 
{
    int n = (int)adj.size();
    components.clear(), adj_cond.clear();

    vector<int> order; // will be a sorted list of G's vertices by exit time

    visited.assign(n, false);

    // first series of depth first searches
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs(i, adj, order);

    // create adjacency list of G^T
    vector<vector<int>> adj_rev(n);
    for (int v = 0; v < n; v++)
        for (int u : adj[v])
            adj_rev[u].push_back(v);

    visited.assign(n, false);
    reverse(order.begin(), order.end());

    vector<int> roots(n, 0); // gives the root vertex of a vertex's SCC

    // second series of depth first searches
    int id = 0;
    for (auto v : order)
        if (!visited[v]) {
            std::vector<int> component;
            dfs(v, adj_rev, component);
            components.push_back(component);
            // int root = *min_element(begin(component), end(component));
            for (auto u : component)
                roots[u] = id;
            id++;
        }

    // add edges to condensation graph
    adj_cond.assign(n, {});
    for (int v = 0; v < n; v++)
        for (auto u : adj[v])
            if (roots[v] != roots[u])
                adj_cond[roots[v]].push_back(roots[u]);
}

void solve() {
    int n, m, t;
    cin >> n >> m >> t;
    vector<vector<int>> g(n);
    vector<bool> possible(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        if (u != t) {
            g[v].push_back(u);
        }
        if (v == t) {
            possible[u] = true;
        }
    }
    vector<vector<int>> dag, comps;
    strongly_connected_components(g, comps, dag);
    int sz = int(comps.size());
    vector<vector<int>> rev(sz);
    for (int i = 0; i < sz; i++) {
        for (int v: dag[i]) {
            rev[v].push_back(i);
        }
    }
    int start = -1;
    for (int i = 0; i < sz; i++) {
        for (int u: comps[i]) {
            if (u == t) {
                start = i;
            }
        }
    }
    assert(start != -1);
    vector<int> dp(sz, -1);
    dp[start] = 1;
    function<int(int)> go = [&](int u) {
        int &ans = dp[u];
        if (ans != -1) return ans;

        int cur = 0;
        for (int v: rev[u]) {
            cur = min(2, cur + go(v));
        }
        return ans = cur;
    };
    vector<int> ans;
    for (int i = 0; i < sz; i++) {
        if (go(i) == 1 && i != start) {
            for (int node: comps[i]) {
                if (possible[node]) {
                    ans.push_back(node);
                }
            }
        }
    }
    // for (int i = 0; i < sz; i++) {
    //     cout << comps[i][0] << " " << dp[comps[i][0]] << endl;
    // }
    // cout << endl;
    cout << ans.size() << '\n';
    sort(ans.begin(), ans.end());
    for (int v: ans) cout << v << '\n';
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

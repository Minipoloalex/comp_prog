#include <bits/stdc++.h>
using namespace std;

/**
 * Usage:
 *  Returns: comps (components) and adj_cond (condensed adjacency list)
 * 
 *  SCC scc;
 *  vector<vector<int>> comps, adj_cond;
 *  scc.run(g, comps, adj_cond);
 */
class SCC {
private:
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

public:
    // input: adj -- adjacency list of G
    // output: components -- the strongy connected components in G
    // output: adj_cond -- adjacency list of G^SCC (by root vertices). Change to by SCC id if required
    void run(vector<vector<int>> const& adj,vector<vector<int>> &components,vector<vector<int>> &adj_cond) 
    {
        int n = int(adj.size());
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
        for (auto v : order)
            if (!visited[v]) {
                vector<int> component;
                dfs(v, adj_rev, component);

                // replace root by the component id to make adj_cond use those indices
                // int root = int(components.size()); // component id
                components.push_back(component);

                int root = *min_element(begin(component), end(component));
                for (auto u : component)
                    roots[u] = root;
            }

        // add edges to condensation graph
        // change size to components size if using component ids
        // adj_cond.assign(components.size(), {});
        adj_cond.assign(n, {});
        for (int v = 0; v < n; v++)
            for (auto u : adj[v])
                if (roots[v] != roots[u])
                    adj_cond[roots[v]].push_back(roots[u]);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
    }

    SCC scc;
    vector<vector<int>> comps, adj_cond;
    scc.run(g, comps, adj_cond);

    vector<int> ans(n);
    for (int i = 0; i < int(comps.size()); i++) {
        for (int node: comps[i]) {
            ans[node] = i + 1;
        }
    }
    cout << comps.size() << '\n';
    for (int kingdom: ans) {
        cout << kingdom << " ";
    }
    cout << '\n';
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

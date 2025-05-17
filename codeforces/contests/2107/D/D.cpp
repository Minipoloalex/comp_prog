#include <bits/stdc++.h>
using namespace std;

// Editorial proof (my proof was just vibes):
/*
Property 1: 2 diameters always share at least one node
- Easy to understand

Property 2: Let (u,v) denote a diameter path, and T denote the tree. Then diam(T∖(u,v)) < diam(T) (strictly smaller)
- Obvious from property 2

Property 3 : In any sequence of positive numbers such that a1 + a2 + … + ak ≤ n such that ai < aj for all 1 ≤ i < j ≤ k, k is at most O(sqrt(n)).
- Obvious from the sum of arithmetic progression
*/

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> vis(n), dist(n), par(n);
    function<void(int,int,int,int&,vector<int>&)> dfs = [&](int u, int p, int d, int &mx_dist, vector<int> &cc) {
        vis[u] = 1; par[u] = p;
        dist[u] = d;
        mx_dist = max(mx_dist, d);
        cc.push_back(u);
        for (int v: g[u]) {
            if (v != p && !vis[v]) {
                dfs(v, u, d + 1, mx_dist, cc);
            }
        }
    };

    vector<tuple<int,int,int>> ans;
    function<void(int)> find_diameter = [&](int u) {
        // cout << "find_diameter(" << u << ")" << endl;
        dist[u] = 0;
        vector<int> cc;
        int mx_dist = 0;
        dfs(u, -1, 0, mx_dist, cc);
        int mx_idx = -1;
        for (int node: cc) {
            if (dist[node] == mx_dist && node > mx_idx) {
                mx_idx = node;
            }
            dist[node] = 0;
            vis[node] = 0;
        }
        cc.clear();
        mx_dist = 0;
        dfs(mx_idx, -1, 0, mx_dist, cc);
        int other_idx = -1;
        for (int node: cc) {
            if (dist[node] == mx_dist && node > other_idx) {
                other_idx = node;
            }
            vis[node] = 0;
            dist[node] = 0;
        }
        vector<int> path;
        int cur = other_idx;
        while (cur != mx_idx) {
            path.push_back(cur);
            cur = par[cur];
        }
        path.push_back(mx_idx);
        for (int p: path) {
            vis[p] = INT_MAX;
        }
        for (int node: cc) {
            if (vis[node] != INT_MAX) {
                find_diameter(node);
            }
        }
        if (other_idx > mx_idx) swap(other_idx, mx_idx);
        ans.emplace_back(mx_dist, mx_idx, other_idx);
    };
    find_diameter(0);

    sort(ans.rbegin(), ans.rend());
    for (auto &[d, u, v]: ans) {
        cout << d + 1 << " " << u + 1 << " " << v + 1 << " ";
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

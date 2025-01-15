#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

void read_tree(int &sz, vvi &g) {
    cin >> sz;
    g.assign(sz, {});
    for (int i = 0; i < sz - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
}

tuple<int,int,int> get_diameter(vvi &g) {
    int far_node = 0, max_dist = 0;
    auto dfs = [&](int u, int p, int depth, auto &&self) -> void {
        if (depth >= max_dist) {
            max_dist = depth;
            far_node = u;
        }
        for (int v: g[u]) {
            if (v != p) {
                self(v, u, depth + 1, self);
            }
        }
    };
    dfs(0, -1, 0, dfs);
    max_dist = 0;
    int start_node = far_node;
    dfs(start_node, -1, 0, dfs);
    int end_node = far_node, diameter = max_dist;
    return make_tuple(start_node, end_node, diameter);
}
int get_mid_node(vvi &g) {
    auto [start_node, end_node, diameter] = get_diameter(g);
    int mid_node;
    auto find_mid = [&](int u, int p, int depth, auto &&self) -> bool {
        bool end = u == end_node;
        for (int v: g[u]) {
            if (v != p) {
                end |= self(v, u, depth + 1, self);
            }
        }
        if (end && depth == diameter / 2) {
            mid_node = u;
        }
        return end;
    };
    find_mid(start_node, -1, 0, find_mid);
    return mid_node;
}
pair<int, vvi> merge_graphs(int n, vvi &g1, int m, vvi &g2, int nd1, int nd2) {
    int sz = n + m;
    vvi g(sz, vector<int>());
    for (int i = 0; i < n; i++) {
        g[i] = g1[i];
    }
    for (int i = 0; i < m; i++) {
        int idx = i + n;
        for (int v: g2[i]) {
            g[idx].push_back(v + n);
        }
    }
    nd2 += n;
    g[nd1].push_back(nd2);
    g[nd2].push_back(nd1);
    return {sz, g};
}

void solve() {
    int n, m;
    vvi g1, g2;
    read_tree(n, g1);
    read_tree(m, g2);
    /*
    There is a better solution:
    instead of literally getting the middle nodes, merging the trees and then calculating the diameter,
    we can just say that the diameter will be the max of (d1, d2 and something like: d1 / 2 + d2 / 2 + 1)
    */
    int nd1 = get_mid_node(g1);
    int nd2 = get_mid_node(g2);
    auto [sz, g] = merge_graphs(n, g1, m, g2, nd1, nd2);
    auto [_, __, ans] = get_diameter(g);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

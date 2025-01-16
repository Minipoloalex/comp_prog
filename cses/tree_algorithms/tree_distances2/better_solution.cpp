#include <bits/stdc++.h>
using namespace std;

vector<int> st;
vector<int64_t> dist;
vector<vector<int>> g;
int n;

void dfs_st(int u, int p, int depth) {
    dist[0] += depth;
    st[u] = 1;
    for (int v: g[u]) {
        if (v != p) {
            dfs_st(v, u, depth + 1);
            st[u] += st[v];
        }
    }
}

void dfs_dist(int u, int p) {
    for (int v: g[u]) {
        if (v != p) {
            dist[v] = dist[u] - st[v] + (n - st[v]);
            dfs_dist(v, u);
        }
    }
}

void solve() {
    cin >> n;
    g.assign(n, vector<int>());
    st.assign(n, 0);
    dist.assign(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs_st(0, -1, 0);
    dfs_dist(0, -1);
    for (int i = 0; i < n; i++) {
        cout << dist[i] << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<map<int,int64_t>> chdist;
vector<int64_t> dist;
vector<int> chcnt;

void dfs_c(int u, int p) {
    int64_t total_dist = 0;
    for (int v: g[u]) {
        if (v != p) {
            dfs_c(v, u);
            chdist[u][v] = dist[v] + chcnt[v] + 1;
            total_dist += chdist[u][v];
            chcnt[u] += chcnt[v] + 1;
        }
    }
    dist[u] = total_dist;
}

void dfs_p(int u, int p) {
    if (p != -1) {
        int64_t p_distances = dist[p] - chdist[p][u];
        int p_children_cnt = chcnt[p] - chcnt[u] - 1;

        int64_t distance = p_distances + p_children_cnt + 1;
        dist[u] += distance;
        chcnt[u] += p_children_cnt + 1;
    }
    for (int v: g[u]) {
        if (v != p) {
            dfs_p(v, u);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    g.assign(n, vector<int>());
    chdist.resize(n);
    dist.assign(n, 0);
    chcnt.assign(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs_c(0, -1);
    dfs_p(0, -1);
    for (int i = 0; i < n; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int MAXN = int(2e5);
const int LOG = 20;

int up[MAXN][LOG];

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int ti;
        cin >> ti;
        ti--;
        up[i][0] = ti;
    }
    for (int p = 1; p < LOG; p++) {
        for (int i = 0; i < n; i++) {
            up[i][p] = up[up[i][p-1]][p-1];
        }
    }
    function<int(int,int)> kth_parent = [&](int u, int k) {
        int node = u;
        for (int p = LOG - 1; p >= 0; p--) {    // don't really need reverse order (that's for LCA)
            if (k & (1 << p)) {
                node = up[node][p];
            }
        }
        return node;
    };
    vector<int> vis(n, 0), id(n, 0), depth(n, 0), ccid(n, 0);
    bool loop = false;
    int loop_id;
    vector<vector<int>> loop_nodes(n);
    int cur_treeid, nxt_treeid = 0;
    int cur_ccid, nxt_ccid = 0;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        int v = up[u][0];
        if (!vis[v]) {
            dfs(v);
        }
        else if (vis[v] == 1) {
            // found the loop
            loop = true;
            loop_id = v;
        }
        else {
            assert(vis[v] == 2);
            cur_ccid = ccid[v];
            if (id[v] != -1) {
                cur_treeid = id[v];
            }
        }
        if (loop) {
            loop_nodes[cur_ccid].push_back(u);
            id[u] = -1;
        }
        else {
            depth[u] = depth[v] + 1;
            id[u] = cur_treeid;
        }
        vis[u] = 2;
        if (loop_id == u) {
            loop = false;
        }
        ccid[u] = cur_ccid;
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cur_ccid = nxt_ccid;
            cur_treeid = nxt_treeid;
            dfs(i);

            // if we end with the same ccid, that means we saw none of the already visited nodes
            if (cur_ccid == nxt_ccid) nxt_ccid++;
            if (cur_treeid == nxt_treeid) nxt_treeid++;
        }
    }
    int nr_ccs = nxt_ccid;      // represents the number of CCs
    loop_nodes.resize(nr_ccs);
    vector<int> loop_indices(n, -1);
    for (vector<int> &cc_loop: loop_nodes) {
        reverse(cc_loop.begin(), cc_loop.end());    // because we introduce them in post-order
        for (int i = 0; i < int(cc_loop.size()); i++) {
            loop_indices[cc_loop[i]] = i;
        }
    }
    auto loop_distance = [&](int a, int b) {
        int ai = loop_indices[a];
        int bi = loop_indices[b];
        int a_ccid = ccid[a];
        assert(ai != -1 && bi != -1);
        if (ai > bi) {
            return int(loop_nodes[a_ccid].size()) - ai + bi;
        }
        return bi - ai;
    };
    auto Dist = [&](int a, int b) {
        if (ccid[a] != ccid[b]) return -1;

        if (id[b] == -1) {  // b in loop
            if (id[a] == -1) {
                // both in loop
                return loop_distance(a, b);
            }
            else {
                // a in tree
                return depth[a] + loop_distance(kth_parent(a, depth[a]), b);
            }
        }
        else {  // b in tree
            if (id[a] != id[b]) {   // in different trees (or a in loop)
                return -1;
            }
            // in same tree, still may not be able to reach
            int diff = depth[a] - depth[b];
            if (diff < 0 || kth_parent(a, diff) != b) return -1;
            return diff;
        }
    };
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        int d = Dist(a, b);
        cout << d << '\n';
    }
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

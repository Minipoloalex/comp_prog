#include <bits/stdc++.h>
using namespace std;

// https://www.hackerearth.com/practice/algorithms/graphs/graph-representation/practice-problems/algorithm/optimal-connectivity-c6ae79ca/

/** Tree class for Binary Lifting */
class Tree {
    private:
        int n;
        vector<int> par;    // pow2ends[i][0] = par[i]
        vector<int> weights;
        vector<vector<int>> pow2ends;   // aka up
        vector<vector<int>> pow2ws;   // aka up
        vector<int> depth;
        const int log2dist;
    public:
        /**
         * Constructs a tree based on a given parent array.
         * @param parents parents[i] in [0, n-1] or -1
         * The parent array. The root (assumed to be node 0) is not included.
         * 
         * If you use a successor graph:
         * - the `par` array construction needs to be changed
         * - the children and depth construction should just be removed
         * Successor graph:
         *   n = int(parents.size());
         *   par = parents;
         *   for (int i = 0; i < n; i++) assert(par[i] < n);
         */
        Tree(const vector<pair<int,int>>& parents)
                : par(parents.size() + 1), weights(parents.size() + 1),
                  log2dist(int(std::ceil(std::log2(parents.size() + 1)))) {
            n = int(parents.size() + 1);
            par[0] = -1;
            for (int i = 0; i < int(parents.size()); i++) {
                par[i + 1] = parents[i].first;
            }
            weights[0] = 0;  // makes sense, because in this problem we want to find the maximum
            for (int i = 0; i < int(parents.size()); i++) weights[i + 1] = parents[i].second;

            pow2ends = vector<vector<int>>(n, vector<int>(log2dist + 1));
            pow2ws = vector<vector<int>>(n, vector<int>(log2dist + 1));
            for (int i = 0; i < n; i++) {
                pow2ends[i][0] = par[i];
                pow2ws[i][0] = weights[i];
            }
            for (int p = 1; p <= log2dist; p++) {
                for (int i = 0; i < n; i++) {
                    int halfway = pow2ends[i][p - 1];
                    if (halfway == -1) {
                        pow2ends[i][p] = -1;
                        pow2ws[i][p] = -1;
                    } else {
                        pow2ends[i][p] = pow2ends[halfway][p - 1];
                        pow2ws[i][p] = max(pow2ws[i][p-1], pow2ws[halfway][p-1]);
                    }
                }
            }

            // Build the depth array
            vector<vector<int>> children(n);
            for (int i = 1; i < n; i++) {
                children[par[i]].push_back(i);
            }

            depth = vector<int>(n);
            vector<int> frontier = {0};
            while (!frontier.empty()) {
                int src = frontier.back();
                frontier.pop_back();
                for (int dst : children[src]) {
                    depth[dst] = depth[src] + 1;
                    frontier.push_back(dst);
                }
            }
        }

        /** @return the kth parent of node n (or -1 if it doesn't exist). */
        pair<int,int> kth_parent(int src, int k) {
            if (k > n) {
                return {-1, 0};
            }
            int at = src;
            int mx = 0;
            for (int pow = 0; pow <= log2dist; pow++) {
                if ((k & (1 << pow)) != 0) {
                    mx = max(mx, pow2ws[at][pow]);
                    at = pow2ends[at][pow];
                    if (at == -1) {
                        break;
                    }
                }
            }
            return {at, mx};
        }

        /** @return the lowest common ancestor of n1 and n2. */
        pair<int,int> lca(int n1, int n2) {
            if (depth[n1] < depth[n2]) {
                return lca(n2, n1);
            }
            int mx = 0;
            tie(n1, mx) = kth_parent(n1, depth[n1] - depth[n2]);
            if (n1 == n2) {
                return {n1, mx};
            }
            for (int i = log2dist; i >= 0; i--) {
                if (pow2ends[n1][i] != pow2ends[n2][i]) {
                    mx = max(mx, pow2ws[n1][i]);
                    mx = max(mx, pow2ws[n2][i]);
                    n1 = pow2ends[n1][i];
                    n2 = pow2ends[n2][i];
                }
            }
            // need to consider the final two edges
            mx = max(mx, pow2ws[n1][0]);
            mx = max(mx, pow2ws[n2][0]);
            return {pow2ends[n1][0], mx};
        }

        /** @return the distance between n1 and n2. */
        int dist(int n1, int n2) {
            return depth[n1] + depth[n2] - 2 * depth[lca(n1, n2).first];
        }
};

void solve() {
    int n;
    cin >> n;
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<pair<int,int>> par(n-1);
    function<void(int,int)> dfs = [&](int src, int p) {
        for (auto &[dst, w]: g[src]) {
            if (dst != p) {
                par[dst-1] = {src, w};
                dfs(dst, src);
            }
        }
    };
    dfs(0, -1);
    Tree t(par);
    int q;
    cin >> q;
    while (q--) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;v--;
        auto [lca, mx] = t.lca(u, v);   // find the max along the path between u and v
        if (mx > w) {
            cout << "YES\n";
        }
        else cout << "NO\n";
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

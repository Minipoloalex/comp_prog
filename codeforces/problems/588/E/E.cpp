#include <bits/stdc++.h>
using namespace std;

const int MAX = 10;
void cut_off(vector<int> &a) {
    sort(a.begin(), a.end());
    if (a.size() > MAX) a.resize(MAX);
}
vector<int> merge(vector<int> &a, vector<int> b) {
    b.insert(b.end(), a.begin(), a.end());
    cut_off(b);
    return b;
}

/** Tree class for Binary Lifting */
class Tree {
    private:
        int n;
        vector<int> par;    // pow2ends[i][0] = par[i]
        vector<vector<int>> cities;
        vector<vector<int>> pow2ends;   // aka up
        vector<vector<vector<int>>> pow2mins;
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
        Tree(const vector<int>& parents, const vector<vector<int>> &cits)
                : par(parents.size() + 1), cities(cits),
                  log2dist(int(std::ceil(std::log2(parents.size() + 1)))) {
            n = int(parents.size() + 1);
            par[0] = -1;
            for (int i = 0; i < int(parents.size()); i++) {
                par[i + 1] = parents[i];
            }

            pow2ends = vector<vector<int>>(n, vector<int>(log2dist + 1));
            pow2mins = vector<vector<vector<int>>>(n, vector<vector<int>>(log2dist + 1));

            for (int i = 0; i < n; i++) {
                pow2ends[i][0] = par[i];
                if (par[i] != -1) {
                    pow2mins[i][0] = cities[par[i]];
                }
            }
            for (int p = 1; p <= log2dist; p++) {
                for (int i = 0; i < n; i++) {
                    int halfway = pow2ends[i][p - 1];
                    if (halfway == -1) {
                        pow2ends[i][p] = -1;
                    } else {
                        pow2ends[i][p] = pow2ends[halfway][p - 1];
                        pow2mins[i][p] = merge(pow2mins[i][p-1], pow2mins[halfway][p-1]);
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
        pair<int,vector<int>> kth_parent(int src, int k) {
            if (k > n) {
                return {-1, vector<int>()};
            }
            int at = src;
            vector<int> mn;
            for (int pow = 0; pow <= log2dist; pow++) {
                if ((k & (1 << pow)) != 0) {
                    mn = merge(mn, pow2mins[at][pow]);
                    at = pow2ends[at][pow];
                    if (at == -1) {
                        break;
                    }
                }
            }
            return {at, mn};
        }

        /** @return the lowest common ancestor of n1 and n2. */
        pair<int,vector<int>> ans(int n1, int n2) {
            if (depth[n1] < depth[n2]) {
                // return lca(n2, n1);
                return ans(n2, n1);
            }
            vector<int> mins;
            if (n1 == n2) {
                return {n1, merge(cities[n1], mins)};
            }
            tie(n1, mins) = kth_parent(n1, depth[n1] - depth[n2]);
            if (n1 == n2) {
                // return n1;
                return {n1, mins};
            }
            for (int i = log2dist; i >= 0; i--) {
                if (pow2ends[n1][i] != pow2ends[n2][i]) {
                    mins = merge(mins, pow2mins[n1][i]);
                    mins = merge(mins, pow2mins[n2][i]);
                    n1 = pow2ends[n1][i];
                    n2 = pow2ends[n2][i];
                }
            }
            // n1 and n2 are nodes one edge below the LCA
            // here, we need to include it only once (since we are including the LCA node, not the two edges)
            mins = merge(mins, pow2mins[n1][0]);

            return {pow2ends[n1][0], mins};
            // return pow2ends[n1][0];
        }

};


void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<int>> cities(n);
    for (int i = 0; i < m; i++) {
        int ci;
        cin >> ci;
        ci--;
        cities[ci].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        cut_off(cities[i]);
    }
    vector<int> par(n - 1);
    function<void(int,int)> dfs = [&](int u, int p) {
        for (int v: g[u]) {
            if (v != p) {
                par[v - 1] = u;   
                dfs(v, u);
            }
        }
    };
    dfs(0, -1);
    Tree t(par, cities);

    while (q--) {
        int u, v, a;
        cin >> u >> v >> a;
        u--;v--;

        // because our tree can't handle 0 jumps (would just do mins = {})
        auto [lca, mins] = t.ans(u,v);
        if (u != lca) mins = merge(mins, cities[u]); 
        if (v != lca) mins = merge(mins, cities[v]);

        int ans_size = min(a, int(mins.size()));
        cout << ans_size;
        for (int i = 0; i < ans_size; i++) {
            cout << " " << mins[i] + 1;
        }
        cout << '\n';
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

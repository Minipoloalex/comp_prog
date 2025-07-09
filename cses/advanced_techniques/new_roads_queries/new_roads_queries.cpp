#include <bits/stdc++.h>
using namespace std;

class dsu {
public:
    int n; vector<int> p;

    dsu(int _n) : n(_n), p(_n, -1) {}

    int set(int x) {
        if (p[x] < 0) return x;
        return p[x] = set(p[x]);
    }

    bool same(int x, int y) {
        return set(x) == set(y);
    }

    int size(int x) {
        return -p[set(x)];
    }

    void unite(int x, int y) {
        int px = set(x), py = set(y);
        if (px == py) return;
        if (size(px) < size(py)) swap(px, py);
        p[px] += p[py];
        p[py] = px;
    }
};

template <typename C>
class edge {
public:
    int u, v; C cost;

    bool operator <(const edge& o) const {
        return cost < o.cost;
    }
};

vector<edge<int>> mstedges;

template <typename C>
class kruskal {
public:
    int n; vector<edge<C>> edges;
    kruskal(int _n, vector<edge<C>>& _e) : n(_n), edges(_e) {}

    bool mst() {
        sort(edges.begin(), edges.end());
        dsu d(n);
        int added = 0;
        for (auto& e : edges) {
            if (!d.same(e.u, e.v)) {
                added++;
                d.unite(e.u, e.v);
                mstedges.push_back(e);
            }
        }
        return added == n - 1;
    }
};

/** Tree class for Binary Lifting */
class Tree {
    private:
        int n;
        vector<int> par;    // pow2ends[i][0] = par[i]
        vector<int> costs;
        vector<vector<int>> pow2ends;   // aka up
        vector<vector<int>> pow2maxs;
        vector<int> depth;
        vector<int> treeid;
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
        Tree(const vector<int>& parents, const vector<int> &csts)
                : par(parents), costs(csts),
                  log2dist(int(std::ceil(std::log2(parents.size() + 1)))) {
            n = int(parents.size());

            pow2ends = vector<vector<int>>(n, vector<int>(log2dist + 1));
            pow2maxs = vector<vector<int>>(n, vector<int>(log2dist + 1));
            for (int i = 0; i < n; i++) {
                pow2ends[i][0] = par[i];
                pow2maxs[i][0] = csts[i];
            }
            for (int p = 1; p <= log2dist; p++) {
                for (int i = 0; i < n; i++) {
                    int halfway = pow2ends[i][p - 1];
                    if (halfway == -1) {
                        pow2ends[i][p] = -1;
                        pow2maxs[i][p] = -1;
                    } else {
                        pow2ends[i][p] = pow2ends[halfway][p - 1];
                        pow2maxs[i][p] = max(pow2maxs[i][p-1], pow2maxs[halfway][p-1]);
                    }
                }
            }

            // Build the depth array
            vector<vector<int>> children(n);
            for (int i = 0; i < n; i++) {
                if (par[i] != -1) {
                    children[par[i]].push_back(i);
                    children[i].push_back(par[i]);
                }
            }

            depth = vector<int>(n);
            treeid = vector<int>(n, -1);
            int curid = 0;
            function<void(int)> bfs = [&](int start) {
                vector<int> frontier = {start};
                treeid[start] = curid;
                while (!frontier.empty()) {
                    int src = frontier.back();
                    frontier.pop_back();
                    for (int dst : children[src]) {
                        if (treeid[dst] == -1) {    // not visited yet
                            depth[dst] = depth[src] + 1;
                            treeid[dst] = curid;
                            frontier.push_back(dst);
                        }
                    }
                }
            };
            // could have handled this outside instead (for this problem)
            // much easier implementation, without having to repeat logic
            for (int i = 0; i < n; i++) {
                if (treeid[i] == -1) {  // not visited
                    bfs(i);
                    curid++;
                }
            }
        }

        /** @return the kth parent of node n (or -1 if it doesn't exist). */
        pair<int,int> kth_parent(int src, int k) {
            if (k > n) {
                return {-1,-1};
            }
            int at = src;
            int mx = 0;
            for (int pow = 0; pow <= log2dist; pow++) {
                if ((k & (1 << pow)) != 0) {
                    mx = max(mx, pow2maxs[at][pow]);
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
            if (treeid[n1] != treeid[n2]) {
                return {-1, -1};
            }
            if (depth[n1] < depth[n2]) {
                return lca(n2, n1);
            }
            int mx;
            tie(n1, mx) = kth_parent(n1, depth[n1] - depth[n2]);
            if (n1 == n2) {
                return {n1, mx};
            }
            for (int i = log2dist; i >= 0; i--) {
                if (pow2ends[n1][i] != pow2ends[n2][i]) {
                    mx = max(mx, pow2maxs[n1][i]);
                    mx = max(mx, pow2maxs[n2][i]);
                    n1 = pow2ends[n1][i];
                    n2 = pow2ends[n2][i];
                }
            }
            // n1 and n2 are nodes one edge below the LCA
            mx = max(mx, pow2maxs[n1][0]);
            mx = max(mx, pow2maxs[n2][0]);
            return {pow2ends[n1][0], mx};
        }

        /** @return the distance between n1 and n2. */
        int dist(int n1, int n2) {
            return depth[n1] + depth[n2] - 2 * depth[lca(n1, n2).first];
        }
};


void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<edge<int>> el;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        el.push_back({a, b, i});
    }
    kruskal<int> k(n, el);
    k.mst();
    vector<vector<pair<int,int>>> g(n);
    for (auto &ed: mstedges) {
        g[ed.u].emplace_back(ed.v, ed.cost);
        g[ed.v].emplace_back(ed.u, ed.cost);
    }
    vector<int> par(n, -1), cost(n);
    function<void(int,int,int)> dfs = [&](int u, int p, int prevcost) {
        if (p != -1) {
            par[u] = p;
            cost[u] = prevcost;
        }
        for (auto &[v, c]: g[u]) {
            if (v != p) {
                dfs(v, u, c);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (par[i] == -1) {
            dfs(i, -1, -1);
        }
    }
    Tree t(par, cost);
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        auto [lca, mx] = t.lca(a, b);
        cout << mx << '\n';
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

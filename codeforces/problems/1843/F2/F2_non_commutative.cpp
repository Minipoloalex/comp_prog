#include <bits/stdc++.h>
using namespace std;

using T = array<int,8>;

/** Tree class for Binary Lifting */
class Tree {
    private:
        int n;
        vector<int> par;    // pow2ends[i][0] = par[i]
        vector<vector<int>> pow2ends;   // aka up
        vector<vector<T>> pow2up;
        vector<vector<T>> pow2down;
        vector<int> depth;
        const int log2dist;

        static constexpr T iden = {0, 0, 0, 0};
        T f(const T &a, const T &b) {
            return {
                max({a[0],b[0],a[2]+b[1]}),
                max(a[1], a[3]+b[1]),
                max(b[2], b[3]+a[2]),
                a[3] + b[3],

                min({a[0+4], b[0+4],a[2+4]+b[1+4]}),
                min( a[1+4], a[3+4]+b[1+4]),
                min( b[2+4], b[3+4]+a[2+4]),
                a[7] + b[7],
            };
        }

        T g(T a, T b) {
            swap(b[1], b[2]);
            swap(b[1+4], b[2+4]);
            return f(a, b);
        }
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
         *   n = int(parents.size());   // instead of n = parents.size() + 1
         *   par = parents;
         *   for (int i = 0; i < n; i++) assert(par[i] < n);
         * 
         * **General checklist for modifications**:
         * - Is N consistent with size of arrays `parents` and `par`
         * - All values in par in [0, n-1] or -1?
         * - Have additional arrays been initialized?
         * - Are children and depth correctly computed? Starts from i = 1 and uses a directed graph from source 0)
         * - If using edge weights, have both (final) edges to the LCA been considered?
         */
        Tree(const vector<int>& parents, const vector<int> &vals)
                : par(parents.size() + 1),
                  log2dist(int(ceil(log2(parents.size() + 1)))) {
            n = int(parents.size() + 1);
            par[0] = -1;
            for (int i = 0; i < int(parents.size()); i++) {
                par[i + 1] = parents[i];
            }

            pow2ends = vector<vector<int>>(n, vector<int>(log2dist + 1));
            pow2up = vector<vector<T>>(n, vector<T>(log2dist + 1));
            pow2down = vector<vector<T>>(n, vector<T>(log2dist + 1));
            for (int i = 0; i < n; i++) {
                pow2ends[i][0] = par[i];
                for (int j = 0; j < 3; j++) {
                    pow2up[i][0][j] = vals[i] > 0 ? vals[i] : 0;
                }
                pow2up[i][0][3] = vals[i];

                for (int j = 4; j < 3+4; j++) {
                    pow2up[i][0][j] = vals[i] < 0 ? vals[i] : 0;
                }
                pow2up[i][0][7] = vals[i];
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 3; j++) {
                    pow2down[i][0][j] = vals[i] > 0 ? vals[i] : 0;
                }
                pow2down[i][0][3] = vals[i];

                for (int j = 4; j < 3+4; j++) {
                    pow2down[i][0][j] = vals[i] < 0 ? vals[i] : 0;
                }
                pow2down[i][0][7] = vals[i];
            }
            for (int p = 1; p <= log2dist; p++) {
                for (int i = 0; i < n; i++) {
                    int halfway = pow2ends[i][p - 1];
                    if (halfway == -1) {
                        pow2ends[i][p] = -1;
                    } else {
                        pow2ends[i][p] = pow2ends[halfway][p - 1];
                        pow2up[i][p] = f(pow2up[i][p-1], pow2up[halfway][p-1]);
                        pow2down[i][p] = f(pow2down[halfway][p-1], pow2down[i][p-1]);
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
        pair<int,T> kth_parent(int src, int k) {
            if (k > n) {
                return {-1, {}};
            }
            int at = src;
            T res = iden;
            for (int pow = 0; pow <= log2dist; pow++) {
                if ((k & (1 << pow)) != 0) {
                    res = f(res, pow2up[at][pow]);
                    at = pow2ends[at][pow];
                    if (at == -1) {
                        break;
                    }
                }
            }
            return {at, res};
        }

        /** @return the lowest common ancestor of n1 and n2. */
        pair<int,T> lca(int n1, int n2) {
            if (depth[n1] < depth[n2]) {
                return lca(n2, n1);
            }
            T resl = iden, resr = iden;
            tie(n1, resl) = kth_parent(n1, depth[n1] - depth[n2]);
            if (n1 == n2) {
                return {n1, f(resl, pow2up[n1][0])};
            }
            for (int i = log2dist; i >= 0; i--) {
                if (pow2ends[n1][i] != pow2ends[n2][i]) {
                    resl = f(resl, pow2up[n1][i]);
                    resr = f(pow2down[n2][i], resr);
                    n1 = pow2ends[n1][i];
                    n2 = pow2ends[n2][i];
                }
            }
            // n1 and n2 are nodes one edge below the LCA
            int ans = pow2ends[n1][0];
            resl = f(resl, pow2up[n1][0]);
            resl = f(resl, pow2up[ans][0]);
            resr = f(pow2down[n2][0], resr);
            return {ans, f(resl, resr)};
        }
};


void solve() {
    int q;
    cin >> q;
    vector<array<int,3>> qs;
    vector<int> parent;
    vector<int> vals = {1};
    for (int i = 0; i < q; i++) {
        char c;
        cin >> c;
        if (c == '+') {
            int vi, xi;
            cin >> vi >> xi;
            vi--;
            parent.push_back(vi);
            vals.push_back(xi);
        }
        else {
            assert(c == '?');
            int u, v, k;
            cin >> u >> v >> k;
            u--;v--;
            qs.push_back({u,v,k});
        }
    }
    Tree t(parent, vals);
    for (int i = 0; i < int(qs.size()); i++) {
        auto &[u, v, k] = qs[i];
        auto [_, aux] = t.lca(u, v);
        int mx = aux[0];
        int mn = aux[0+4];
        // cout << mn << " " << mx << " ";
        if (mn <= k && k <= mx) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
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

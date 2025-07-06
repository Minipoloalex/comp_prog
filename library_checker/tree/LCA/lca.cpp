#include <bits/stdc++.h>
using namespace std;

/** Tree class for Binary Lifting */
class Tree {
    private:
        int n;
        vector<int> par;    // pow2ends[i][0] = par[i]
        vector<vector<int>> pow2ends;   // aka up
        vector<int> depth;
        const int log2dist;
    public:
        /**
         * Constructs a tree based on a given parent array.
         * @param parents
         * The parent array. The root (assumed to be node 0) is not included.
         */
        Tree(const vector<int>& parents)
                : par(parents.size() + 1),
                  log2dist(std::ceil(std::log2(parents.size() + 1))) {
            n = int(parents.size() + 1);
            par[0] = -1;
            for (int i = 0; i < int(parents.size()); i++) {
                par[i + 1] = parents[i];
            }

            pow2ends = vector<vector<int>>(n, vector<int>(log2dist + 1));
            for (int i = 0; i < n; i++) {
                pow2ends[i][0] = par[i];
            }
            for (int p = 1; p <= log2dist; p++) {
                for (int i = 0; i < par.size(); i++) {
                    int halfway = pow2ends[i][p - 1];
                    if (halfway == -1) {
                        pow2ends[i][p] = -1;
                    } else {
                        pow2ends[i][p] = pow2ends[halfway][p - 1];
                    }
                }
            }

            // Build the depth array
            vector<vector<int>> children(n);
            for (int i = 1; i < par.size(); i++) {
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
        int kth_parent(int src, int k) {
            if (k > n) {
                return -1;
            }
            int at = src;
            for (int pow = 0; pow <= log2dist; pow++) {
                if ((k & (1 << pow)) != 0) {
                    at = pow2ends[at][pow];
                    if (at == -1) {
                        break;
                    }
                }
            }
            return at;
        }

        /** @return the lowest common ancestor of n1 and n2. */
        int lca(int n1, int n2) {
            if (depth[n1] < depth[n2]) {
                return lca(n2, n1);
            }
            n1 = kth_parent(n1, depth[n1] - depth[n2]);
            if (n1 == n2) {
                return n1;
            }
            for (int i = log2dist; i >= 0; i--) {
                if (pow2ends[n1][i] != pow2ends[n2][i]) {
                    n1 = pow2ends[n1][i];
                    n2 = pow2ends[n2][i];
                }
            }
            return n1 == 0 ? 0 : pow2ends[n1][0];
        }

        /** @return the distance between n1 and n2. */
        int dist(int n1, int n2) {
            return depth[n1] + depth[n2] - 2 * depth[lca(n1, n2)];
        }
};


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> ps(n - 1);
    for (auto &p: ps) cin >> p;
    Tree t(ps);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << t.lca(u, v) << '\n';
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

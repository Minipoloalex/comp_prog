#include <bits/stdc++.h>
using namespace std;

/** Tree class for Binary Lifting */
class Tree {
    public:
        int n;
        vector<int> par;    // pow2ends[i][0] = par[i]
        vector<vector<int>> pow2ends;   // aka up
        vector<int> depth;
        const int log2dist;
    
        /**
         * Constructs a tree based on a given parent array.
         * @param parents
         * The parent array. The root (assumed to be node 0) is not included.
         * 
         * For this problem, the template had to be modified
         * It's a successor graph instead of a tree.
         */
        Tree(const vector<int>& parents)
                : par(parents.size()),
                  log2dist(int(std::ceil(std::log2(parents.size() + 1)))) {
            n = int(parents.size());
            for (int i = 0; i < int(parents.size()); i++) {
                par[i] = parents[i];
            }

            pow2ends = vector<vector<int>>(n, vector<int>(log2dist + 1));
            for (int i = 0; i < n; i++) {
                pow2ends[i][0] = par[i];
            }
            for (int p = 1; p <= log2dist; p++) {
                for (int i = 0; i < n; i++) {
                    int halfway = pow2ends[i][p - 1];
                    if (halfway == -1) {
                        pow2ends[i][p] = -1;
                    } else {
                        pow2ends[i][p] = pow2ends[halfway][p - 1];
                    }
                }
            }

            // // Build the depth array
            // vector<vector<int>> children(n);
            // for (int i = 0; i < n; i++) {
            //     if (par[i] != -1) {
            //         children[par[i]].push_back(i);   
            //     }
            // }

            // depth = vector<int>(n);
            // vector<int> frontier = {0};
            // while (!frontier.empty()) {
            //     int src = frontier.back();
            //     frontier.pop_back();
            //     for (int dst : children[src]) {
            //         depth[dst] = depth[src] + 1;
            //         frontier.push_back(dst);
            //     }
            // }
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
    int n;
    int64_t k;
    cin >> n >> k;
    vector<int> x(2 * n);
    for (int i = 0; i < n; i++) {
        int xi;
        cin >> xi;
        x[i] = x[n + i] = xi;
    }
    vector<int64_t> pref(2*n + 1, 0);
    for (int i = 0; i < 2*n; i++) {
        pref[i + 1] = pref[i] + x[i];
    }

    // needs the +1 because it should include all nodes that can be targeted in the successor graph
    // for instance if the array can be just one subarray, all indices would point to 2 * n (so 2*n needs to be included in the graph)
    vector<int> suc(2*n+1, -1);
    for (int i = 0; i < n; i++) {
        int j = int(upper_bound(pref.begin() + i, pref.end(), k + pref[i]) - pref.begin() - 1);
        j--;    // because pref has size + 1
        suc[i] = j + 1;    // but we want to connect i to j + 1: with [i,j] valid subarray

        // e.g. if n = 8, we don't need an edge pointing to 16 (since we will start only with idx <= 7)
        if (j + 1 + n < 2*n) suc[i + n] = j + 1 + n;
    }
    Tree t(suc);
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        // by reaching this position, we know we went through nodes [i, n + i)
        int dst = n + i;
        int at = i;
        int sm = 0;
        for (int pow = t.log2dist; pow >= 0; pow--) {
            int nxt = t.pow2ends[at][pow];
            if (nxt != -1 && nxt < dst) {   // before reaching it
                at = nxt;
                sm += 1 << pow;
            }
        }
        sm++;   // final movement
        ans = min(ans, sm);
    }
    cout << ans << '\n';
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

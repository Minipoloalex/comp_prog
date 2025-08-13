#include <bits/stdc++.h>
using namespace std;



/** Tree class for Binary Lifting */
class Tree {
    private:
        int n;
        vector<int> par;    // pow2ends[i][0] = par[i]
        vector<vector<int>> pow2ends;   // aka up
        vector<vector<int64_t>> pow2vals;   // aka up
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
         * - If performing non-commutative operations, you should be careful when combining two paths (in the LCA)
         */
        Tree(const vector<int>& parents)
                : par(parents.size()),
                  log2dist(int(ceil(log2(parents.size() + 1)))) {
            n = int(parents.size());
            par = parents;

            pow2ends = vector<vector<int>>(n, vector<int>(log2dist + 1));
            pow2vals = vector<vector<int64_t>>(n, vector<int64_t>(log2dist + 1));
            for (int i = 0; i < n; i++) {
                pow2ends[i][0] = par[i];
                pow2vals[i][0] = i;
            }
            for (int p = 1; p <= log2dist; p++) {
                for (int i = 0; i < n; i++) {
                    int halfway = pow2ends[i][p - 1];
                    if (halfway == -1) {
                        pow2ends[i][p] = -1;
                    } else {
                        pow2vals[i][p] = pow2vals[i][p-1]+pow2vals[halfway][p-1];
                        pow2ends[i][p] = pow2ends[halfway][p - 1];
                    }
                }
            }
        }

        /** @return the kth parent of node n (or -1 if it doesn't exist). */
        pair<int,int64_t> kth_parent(int src, int k) {
            if (k > n) {
                return {-1, 0};
            }
            int at = src;
            int64_t ans = 0;
            for (int pow = 0; pow <= log2dist; pow++) {
                if ((k & (1 << pow)) != 0) {
                    ans += pow2vals[at][pow];
                    at = pow2ends[at][pow];
                    if (at == -1) {
                        break;
                    }
                }
            }
            return {at, ans};
        }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> nxt(n);
    vector<int> d(n+1,0);
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;j+=i)
            d[j]++;
    for (int i = 0; i < n; i++) {
        nxt[i] = (i+d[i]) % n;
    }
    vector<int> ccid(n), cycle_length(n), depth(n);
    vector<int> vis(n);
    Tree t(nxt);
    int timer = 0;
    int cur = timer;
    int cycle_orig = -1;
    int cur_cycle_length = 0;
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        int v = nxt[u];
        if (vis[v] == 2) {
            // ccid[u] = ccid[v];  // need to update previous as well
            cur = ccid[v];
        }
        else if (vis[v] == 1) {
            // cycle detected
            cycle_orig = v;
        }
        else {
            dfs(v);
        }

        vis[u] = 2;
        ccid[u] = cur;
        if (cycle_orig != -1) {
            cur_cycle_length++;
            if (cycle_orig == u) {
                cycle_length[ccid[u]] = cur_cycle_length;
                cycle_orig = -1;
                cur_cycle_length = 0;
            }
        }
        else {
            depth[u] = depth[v] + 1;
        }
    };
    for (int i = 0; i < n; i++) {
        cur_cycle_length = 0;
        if (!vis[i]) dfs(i);
        if (cur == timer) timer++;
        cur = timer;
    }
    int64_t ans = INT64_MAX;
    int id = -1;
    for (int i = 0; i < n; i++) {
        int length_of_cycle = cycle_length[ccid[i]];
        if (length_of_cycle + depth[i] >= k) {
            auto [kth, curans] = t.kth_parent(i, k);
            if (curans < ans) {
                ans = curans;
                id = i;
            }
        }
    }
    if (id == -1) {
        cout << id << '\n';
    }
    else {
        // cout << ans << endl;
        for (int i = 0; i < k; i++) {
            cout << id << " ";
            id = nxt[id];
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

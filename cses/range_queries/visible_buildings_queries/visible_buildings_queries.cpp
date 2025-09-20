#include <bits/stdc++.h>
using namespace std;

/** Tree class for Binary Lifting */
struct Tree {
        int n;
        vector<int> par;    // pow2ends[i][0] = par[i]
        const int log2dist;
        vector<vector<int>> pow2ends;   // aka up
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
        Tree(const vector<int>& parents)
                : par(parents.size() + 1),
                  log2dist(int(ceil(log2(parents.size() + 1)))) {
            n = int(parents.size());
            par = parents;

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
        }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> h(n);
    for (auto &hi: h) cin >> hi;

    vector<int> nxt_greater(n + 1);
    stack<int> s;
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && h[s.top()] <= h[i]) {
            s.pop();
        }
        nxt_greater[i] = s.empty() ? n : s.top();
        s.push(i);
    }
    nxt_greater[n] = n;

    Tree bl(nxt_greater);
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        int node = a, cnt = 1;  // need to account for "a"
        // Count how many jumps are allowed before exiting [a,b]
        for (int i = bl.log2dist; i >= 0; i--) {
            if (bl.pow2ends[node][i] <= b) {
                cnt += (1 << i);
                node = bl.pow2ends[node][i];
            }
        }
        cout << cnt << '\n';
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

#include <bits/stdc++.h>
using namespace std;


using ll = long long;
#define sz(v) int((v).size())

/** Tree class for Binary Lifting */
class Tree {
    private:
        int n;
        vector<int> par;    // pow2ends[i][0] = par[i]
        vector<vector<int>> pow2ends;   // aka up
        vector<int> depth;
        vector<int> age;
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
         */
        Tree(const vector<int>& parents, vector<int> const& _age)
                : par(parents.size() + 1),
                  log2dist(int(ceil(log2(parents.size() + 1)))) {
            n = int(parents.size());
            par = parents;
            age = _age;

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
            // n1 and n2 are nodes one edge below the LCA
            return pow2ends[n1][0];
        }

        /** @return the distance between n1 and n2. */
        int dist(int n1, int n2) {
            return depth[n1] + depth[n2] - 2 * depth[lca(n1, n2)];
        }

        int handle_move(int u, pair<int,int> &party) {
            for (int i = log2dist; i >= 0; i--) {
                int new_node = pow2ends[u][i];
                if (age[new_node] <= party.second) {
                    u = new_node;
                }
            }
            return u;
        }
};

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

const int MAX_AGE = int(1e5);

void solve() {
    int n, m; cin >> n >> m;
    vector<int> age(n), p(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        cin >> age[i];
        cin >> p[i];
        p[i]--;
        if (i > 0) {
            g[p[i]].push_back(i);
        }
    }
    vector<vector<pair<int,int>>> parties(n);
    vector<vector<pair<int,int>>> finalparties(n);
    for (int i = 0; i < m; i++) {
        int oj, lj, rj;
        cin >> oj >> lj >> rj;
        oj--;
        parties[oj].emplace_back(lj, rj);
    }
    Tree t(p, age);
    FT ft(MAX_AGE + 2);
    function<void(int)> dfs1 = [&](int u) {
        for (int v: g[u]) {
            dfs1(v);
        }
        for (auto &party: parties[u]) {
            int f = t.handle_move(u, party);
            finalparties[f].push_back(party);
        }
    };
    dfs1(0);
    vector<int> ans(n);
    function<void(int)> dfs = [&](int u) {
        for (auto &[l, r]: finalparties[u]) {
            // cout << u << " " << l << " " << r << endl;
            ft.update(l,  +1);
            ft.update(r+1,-1);
        }

        ans[u] = ft.query(age[u]+1);    // [0, age[u]]
        for (int v: g[u]) {
            dfs(v);
        }
        for (auto &[l, r]: finalparties[u]) {
            ft.update(l,  -1);
            ft.update(r+1,+1);
        }
    };
    // cout << "here" << endl;
    dfs(0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << '\n';
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

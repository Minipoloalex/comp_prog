#include <bits/stdc++.h>
using namespace std;

// supports point update, range query
template <typename T>
struct seg_tree {
    int n;
    vector<T> t;

    // neutral element: inf in min seg_tree, 0 in sum seg_tree, ...
    static constexpr T iden = numeric_limits<T>::min();

    seg_tree(int sz) : n(sz), t(2 * sz, iden) {}

    seg_tree(const vector<T>& arr) : n(int(arr.size())), t(2 * n) {
        build(arr);
    }
	void build(const vector<T> &arr) {
		for (int i = 0; i < n; i++)
            update(i, arr[i]);
	}

    T f(const T& a, const T& b) {
        return max(a, b);
    }

    void update(int p, T val) { // point update in position p
        t[p += n] = val;
        for (p >>= 1; p > 0; p >>= 1)
            t[p] = f(t[p << 1], t[p << 1 ^ 1]);
    }

    T query(int l, int r) { // range [l, r)
        T res = iden;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = f(res, t[l++]);
            if (r & 1) res = f(res, t[--r]);
        }
        return res;
    }
};

typedef vector<int> vi;

// Assumes the Segment Tree handles intervals inclusive on both ends: [l, r]
/**
 * Usage:
 * 1. HLD hld(n);
 *    hld.add_edge(u, v); (many times)
 *    hld.build_tree();
 *    hld.build_values(vals);
 *
 * 2. HLD hld(g);
 *    hld.build_tree();
 *    hld.build_values(vals);
 */
template <bool VALS_ON_EDGES>
struct HLD {
	int n, timer = 0;
	vector<vi> g;   // adjacency list

    // parents, size of subtree, head/top of the heavy edges chain, position in the euler tour
	vi par, sz, head, pos;

    seg_tree<int> tree;

    HLD(int _n): n(_n), g(n),
        par(n, -1), sz(n, 1), head(n, 0), pos(n), tree(n) {}

	HLD(const vector<vi> &_g): n(int(_g.size())), g(_g),
        par(n, -1), sz(n, 1), head(n, 0), pos(n), tree(n) {}

    // u, v in [0, n - 1]
    void add_edge(int u, int v) {
        g[u].push_back(v);
    }

    // Populates the vectors based on the tree structure
    void build_tree() {
        dfs_sz(0, -1);
        dfs_hld(0);
    }

    // Populates the segment tree with the node values (can be edge values)
    // build_tree must be called first
    void build_values(const vector<int> &base_values) {
        if constexpr (VALS_ON_EDGES) {
            assert(base_values[0] == INT_MAX);
        }
        vector<int> vals(n);
        for (int u = 0; u < n; u++) {
            vals[pos[u]] = base_values[u];
        }
        tree.build(vals);
    }

    // Computes the sizes of the subtrees at each node
    // Makes sure adj[u][0] is the heavy child (erases parents from child's adjacency list)
	void dfs_sz(int u, int p) {
        par[u] = p;
        auto it = find(g[u].begin(), g[u].end(), p);
        if (it != g[u].end()) g[u].erase(it); // erase parent from adjacency list

        for (int &v: g[u]) {
            dfs_sz(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
	}

    // Gives unique ids to all nodes, ensuring heavy chains have continuous ids
    // For each node, saves the "head" (or top) of its chain
	void dfs_hld(int u) {
		pos[u] = timer++;
		for (int v: g[u]) {
			head[v] = (v == g[u][0] ? head[u] : v);
			dfs_hld(v);
		}
	}

    // op is called on [l, r): exclusive on the right
	template <class B>
    void process(int u, int v, B op) {
		while (true) {
            // make sure v was visited after u
			if (pos[u] > pos[v]) swap(u, v);

            // once both lie in the same chain (it's their LCA chain)
			if (head[u] == head[v]) break;

			op(pos[head[v]], pos[v] + 1);
            v = par[head[v]];
		}

        // doesn't include the head (u) if treating values on edges
		op(pos[u] + VALS_ON_EDGES, pos[v] + 1);
	}
	void modify_vertex(int u, int val) {
		process(u, u, [&](int l, int r) {
            tree.update(l, val);
        });
		// Or use: tree.update(pos[u], val);
	}
	int query_path(int u, int v) {
		int mx = INT_MIN;
		process(u, v, [&](int l, int r) {
            mx = max(mx, tree.query(l, r));
		});
		return mx;
	}
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> vals(n);
    for (auto &v: vals) cin >> v;

    HLD<false> hld(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        hld.add_edge(a, b);
        hld.add_edge(b, a);
    }
    hld.build_tree();
    hld.build_values(vals);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s, x;
            cin >> s >> x;
            s--;
			hld.modify_vertex(s, x);
        }
        else {
            assert(type == 2);
            int a, b;
            cin >> a >> b;
            a--;b--;
            int res = hld.query_path(a, b);
            cout << res << " ";
        }
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

#include <bits/stdc++.h>
using namespace std;

/**
 * - All indices are 0-indexed
 * - All intervals are inclusive in both endpoints: [l, r]
 */
template <class Info, class Tag>
class LazySegTree {
  private:
	const int n;
	vector<Info> tree;
	vector<Tag> lazy;

	/**
	 * Example usage:
	 * int idx = segtree.find_first(
	 *   [&](const Info &pref) {
	 *     return pref.sum >= K;
	 *   }
	 * );
	 * Return true iff the prefix Info satisfies the function.
	 * Used for walks on the Segment Tree: to find the smallest prefix that satisfies the function
	 */
	// using Pred = function<bool(const Info&)>;

	// left and right children
	inline int lc(int i) { return i << 1; }
    inline int rc(int i) { return (i << 1) | 1; }

	/** All indices are inclusive */
    inline bool outside(int l, int r, int ql, int qr) {
        return qr < l || r < ql;
    }
	/** All indices are inclusive */
    inline bool inside(int l, int r, int ql, int qr) {
        return ql <= l && r <= qr;
    }
	/** builds the segtree values in O(N) time */
	void build(int node, int l, int r, const vector<Info> &a) {
		if (l == r) {
			tree[node] = a[l];
		}
        else {
			int m = (l + r) / 2;
			int left = lc(node);
			int right = rc(node);
			build(left, l, m, a);
			build(right, m + 1, r, a);
			tree[node] = tree[left] + tree[right];
		}
	}

	/** applies update to lazy[node] and tree[node] */
	void apply(int node, int l, int r, const Tag &update) {
		tree[node].apply(update, l, r);
		lazy[node].apply(update);
	}

	/** pushes lazy updates down to the children of node */
	void push_down(int node, int l, int r) {
		int m = (l + r) / 2;
		apply(lc(node), l, m, lazy[node]);
		apply(rc(node), m + 1, r, lazy[node]);
		lazy[node] = Tag();
	}

	void range_update(int node, int l, int r, int ql, int qr, const Tag &update) {
		if (outside(l, r, ql, qr)) return;
        if (inside(l, r, ql, qr)) {
			apply(node, l, r, update);
		}
		else {
			push_down(node, l, r);
			int m = (l + r) / 2;
			int left = lc(node);
			int right = rc(node);
			range_update(left, l, m, ql, qr, update);
			range_update(right, m + 1, r, ql, qr, update);
			tree[node] = tree[left] + tree[right];
		}
	}

	Info range_query(int node, int l, int r, int ql, int qr) {
		if (outside(l, r, ql, qr)) return Info();
		if (inside(l, r, ql, qr)) return tree[node];
		push_down(node, l, r);
		int m = (l + r) / 2;
		return range_query(lc(node), l, m, ql, qr) +
		       range_query(rc(node), m + 1, r, ql, qr);
	}

    template<class Pred>
	int find_first(int node, int l, int r, const Info &acc, const Pred &pred) {
		Info full = acc + tree[node];
		if (!pred(full)) return -1;
		if (l == r) return l;

		push_down(node, l, r);
		int m = (l + r) / 2;
		int left = lc(node);
		int right = rc(node);

		if (pred(acc + tree[left])) {
			return find_first(left, l, m, acc, pred);
		}
		return find_first(right, m + 1, r, acc + tree[left], pred);
	}

  public:
	LazySegTree() {}

	LazySegTree(int _n) : n(_n) {
		// or just use: 4 * n
		tree.assign(4 << __lg(n), Info());
		lazy.assign(4 << __lg(n), Tag());
	}

	/*
	// Perfectly balanced tree
	// For easier debugging of internal seg tree nodes
	LazySegTree(int orig_n) {		
		n = 1;
        while (n < orig_n) n <<= 1;
        tree.assign(2 * n, Info());
		lazy.assign(2 * n, Tag());
	}
	*/

	LazySegTree(const vector<Info> &a) : LazySegTree(int(a.size())) {
		build(a);
	}

    /**
     * Builds the segment tree based on the given array.
     * Assumes the array has the exact same size of the Segment Tree
     */
    void build(const vector<Info> &a) {
        build(1, 0, n - 1, a);
    }

	/**
	 * Walk on the Seg Tree: find the smallest prefix that satisfies the function pred
	 * Returns the index i of the prefix [0, i] (0-indexed) where the function is first true
	 */
    template<class Pred>
	int find_first(Pred pred) {
		return find_first(1, 0, n - 1, Info(), pred);
	}

	/** updates [ql, qr] (0-indexed) with the arbitrary update chosen */
	void range_update(int ql, int qr, const Tag &update) {
		range_update(1, 0, n - 1, ql, qr, update);
	}

	/** @return result of range query on [ql, qr] (0-indexed) */
	Info range_query(int ql, int qr) {
		return range_query(1, 0, n - 1, ql, qr);
	}
};

enum UpdateType { SET, NONE };

// Keeps track of Lazy Updates
struct Tag {
	// Default values
	UpdateType type = NONE;
	int value = 0;

	/* Combining lazy updates in a node */
	void apply(const Tag &update) {
        if (update.type == SET) {
			type = SET;
			value = update.value;
		}
	}
};

// Keeps track of Segment Tree information
struct Info {
	// Default values
	int mx = INT_MIN;

	/**
	 * Update the values of a node based on a lazy update.
	 * The lazy update will be "kept" on this node, so here we "fully" update it.
	 */
	void apply(const Tag &update, int l, int r) {
		if (update.type == SET) {
			mx = update.value;
		}
	}
};

/** @return result of joining nodes a and b together */
Info operator+(const Info &a, const Info &b) {
	return {max(a.mx, b.mx)};
}

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
template <class Info, class Tag, bool VALS_ON_EDGES>
struct HLD {
	int n, timer = 0;
	vector<vi> g;   // adjacency list

    // parents, size of subtree, head/top of the heavy edges chain, position in the euler tour
	vi par, sz, head, pos;

    LazySegTree<Info, Tag> tree;

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
    void build_values(const vector<Info> &base_values) {
        if constexpr (VALS_ON_EDGES) {
            assert(base_values[0] == Info());
        }
        vector<Info> vals(n);
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
	void modify_path(int u, int v, Tag update) {
		process(u, v, [&](int l, int r) {
            if (l <= r - 1) {
                tree.range_update(l, r - 1, update);
            }
        });
	}
	Info query_path(int u, int v) {
		Info res;
		process(u, v, [&](int l, int r) {
            if (l <= r - 1) {
                res = res + tree.range_query(l, r - 1);
            }
		});
		return res;
	}
	// Info query_subtree(int u) {
    //     int l = pos[u] + VALS_ON_EDGES;
    //     int r = pos[u] + sz[u] - 1;
    //     return (l <= r ? seg.range_query(l, r) : Info());
	// }
    // void modify_subtree(int u, Tag update) {
    //     int l = pos[u] + VALS_ON_EDGES;
    //     int r = pos[u] + sz[u] - 1;
    //     if (l <= r) {
    //         tree.range_update(l, r, update);
    //     }
    // }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<Info> vals(n);
    for (auto &v: vals) cin >> v.mx;

    HLD<Info,Tag,false> hld(n);
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
            hld.modify_path(s, s, Tag{SET, x});
        }
        else {
            assert(type == 2);
            int a, b;
            cin >> a >> b;
            a--;b--;
            Info res = hld.query_path(a, b);
            cout << res.mx << " ";
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

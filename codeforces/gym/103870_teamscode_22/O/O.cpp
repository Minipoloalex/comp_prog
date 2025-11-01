#include <bits/stdc++.h>
using namespace std;

/**
 * - All indices are 0-indexed
 * - All intervals are inclusive in both endpoints: [l, r]
 */
template <class Info, class Tag>
class LazySegTree {
  private:
	int n;
	vector<Info> tree;
	vector<Tag> lazy;

	/**
	 * Example usage of find_first:
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
     * Assumes the array has the exact size previously passed to the Segment Tree
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
	int value = INT_MIN;	// only important if type is not None

	/* Combining lazy updates in a node */
	void apply(const Tag &update) {
        if (update.type == SET) {
			type = SET;
			value = max(value, update.value);
		}
	}
};

// Keeps track of Segment Tree information
struct Info {
	// Default values
	int mn = INT_MAX;

	/**
	 * Update the values of a node based on a lazy update.
	 * The lazy update will be "kept" on this node, so here we "fully" update it.
	 */
	void apply(const Tag &update, int l, int r) {
		if (update.type == SET) {
            if (mn == INT_MAX) mn = update.value;
			else mn = max(mn, update.value);
		}
	}
};

/** @return result of joining nodes a and b together */
Info operator+(const Info &a, const Info &b) {
	return {min(a.mn, b.mn)};
}

void solve() {
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    using E = array<int,6>;
    vector<E> events; events.reserve(k+q);
    int R = 0, Q = 1;
    for (int i = 0; i < k; i++) {
        int xa, xb, yr;
        cin >> xa >> xb >> yr;
        events.push_back({yr, R, xa, xb, -1, -1});
    }
    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        events.push_back({max(b,d), Q, min(a,c), max(a,c), min(b,d), i});
    }
    sort(events.begin(), events.end());
    LazySegTree<Info,Tag> st(m+1);    // lazy segtree over x's
    st.range_update(0, m, Tag{SET,INT_MIN});

    vector<bool> res(q);
    for (auto &[y, type, xa, xb, yl, id]: events) {
        if (type == R) {
            if (xa < xb) {  // otherwise, it's useless
                st.range_update(xa, xb-1, Tag{SET, y});
            }
        }
        else {
            assert(type == Q);
            bool ans;
            if (xa == xb) {
                ans = true;
            }
            else {
                int mn = st.range_query(xa, xb-1).mn;
                ans = mn >= yl;
            }
            res[id] = ans;
        }
    }
    for (bool ans: res) {
        cout << (ans ? "YES": "NO") << '\n';
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

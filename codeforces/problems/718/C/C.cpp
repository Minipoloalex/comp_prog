#include <bits/stdc++.h>
using namespace std;


const int64_t MOD = int64_t(1e9) + 7;

const int SZ = 2;
typedef array<int64_t, SZ> vec;
typedef array<vec, SZ> MAT;

MAT zeros = MAT{vec{0, 0}, vec{0, 0}};
MAT iden = MAT{vec{1, 0}, vec{0, 1}};
MAT fib_base = MAT{vec{0, 1}, vec{1, 1}};

MAT matadd(const MAT &a, const MAT &b) {
    MAT c = zeros;
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            c[i][j] = a[i][j] + b[i][j];
            if (c[i][j] >= MOD) c[i][j] -= MOD;
        }
    }
    return c;
}

MAT matmult(const MAT &a, const MAT &b) {
    MAT c = zeros;
    for (int i = 0; i < SZ; ++i) {
        for (int k = 0; k < SZ; ++k) {
            for (int j = 0; j < SZ; ++j) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= MOD;
            }
        }
    }
    return c;
}

MAT matexpo(MAT a, int64_t b) {
    MAT res = iden;
    while (b > 0) {
        if (b & 1) res = matmult(res, a);
        b >>= 1;
        a = matmult(a, a);
    }
    return res;
}

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
			int m = (l + r) >> 1;
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
		int m = (l + r) >> 1;
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
			int m = (l + r) >> 1;
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
		int m = (l + r) >> 1;
		return range_query(lc(node), l, m, ql, qr) +
		       range_query(rc(node), m + 1, r, ql, qr);
	}

    template<class Pred>
	int find_first(int node, int l, int r, const Info &acc, const Pred &pred) {
		Info full = acc + tree[node];
		if (!pred(full)) return -1;
		if (l == r) return l;

		push_down(node, l, r);
		int m = (l + r) >> 1;
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

enum UpdateType { ADD_FIB, NONE };

// Keeps track of Lazy Updates
struct Tag {
	// Default values
	UpdateType type = NONE;
	MAT fib_mat = iden;	// only important if type is not None

	/* Combining lazy updates in a node */
	void apply(const Tag &update) {
        if (update.type == ADD_FIB) {
            type = ADD_FIB;
            fib_mat = matmult(update.fib_mat, fib_mat);
        }
	}
};

// Keeps track of Segment Tree information
struct Info {
	// Default values
	MAT mat = zeros;

	/**
	 * Update the values of a node based on a lazy update.
	 * The lazy update will be "kept" on this node, so here we "fully" update it.
	 */
	void apply(const Tag &update, int l, int r) {
        // matrix multiplication is distributive over addition
		if (update.type == ADD_FIB) {
            mat = matmult(mat, update.fib_mat);
        }
	}
};

/** @return result of joining nodes a and b together */
Info operator+(const Info &a, const Info &b) {
	return {matadd(a.mat, b.mat)};
}

// instead of storing matrices in the segment tree
// we could use vectors (of the linear recurrence instead)
// treat the segment tree information as the "base" values

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Info> a(n);
    MAT base = fib_base;
    for (auto &info_ai: a) {
        int ai;
        cin >> ai;
        info_ai = Info(matexpo(base, ai));
    }

    LazySegTree<Info, Tag> st(a);
    while (m--) {
        int tp, l, r;
        cin >> tp >> l >> r;
        l--;r--;
        if (tp == 1) {
            int x;
            cin >> x;
            st.range_update(l, r, Tag{ADD_FIB, matexpo(base, x)});
        }
        else {
            assert(tp == 2);
            Info res = st.range_query(l, r);
            cout << res.mat[0][1] << '\n';
        }
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

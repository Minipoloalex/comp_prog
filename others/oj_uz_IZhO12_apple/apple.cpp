#include <bits/stdc++.h>
using namespace std;

// Tested on https://oj.uz/problem/view/IZhO12_apple (range updates & range queries)

template <class Info, class Tag>
class SparseSegTree {
private:
    struct Node {
        Info info;
        Tag lazy;
        bool hasLazy;
        Node* left;
        Node* right;
        Node()
          : info(), lazy(), hasLazy(false), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int L, R;

    // Check if [ql,qr] is completely outside [l,r]
    inline bool outside(int l, int r, int ql, int qr) {
        return qr < l || r < ql;
    }
    // Check if [l,r] is completely inside [ql,qr]
    inline bool inside(int l, int r, int ql, int qr) {
        return ql <= l && r <= qr;
    }

    // Recompute this node's info from its children
    // Info() + left + right: supports associative
    void pull(Node* node) {
        node->info = Info();
        if (node->left)  node->info = node->info + node->left->info;
        if (node->right) node->info = node->info + node->right->info;
    }

    // Apply an update to this node
    void apply(Node* node, const Tag &update, int l, int r) {
        node->info.apply(update, l, r);
        node->lazy.apply(update);
        node->hasLazy = true;
    }

    // Push a pending update down to children
    void push(Node* node, int l, int r) {
        if (!node->hasLazy) return;
        int m = l + (r - l) / 2;
        if (!node->left)  node->left  = new Node();
        if (!node->right) node->right = new Node();
        apply(node->left,  node->lazy, l,   m);
        apply(node->right, node->lazy, m+1, r);
        node->lazy    = Tag();
        node->hasLazy = false;
    }

    // Node*& is required because we change the pointer
    void update(Node* &node, int l, int r, int ql, int qr, const Tag &updateTag) {
        if (outside(l, r, ql, qr)) return;
        if (!node) node = new Node();
        if (inside(l, r, ql, qr)) {
            apply(node, updateTag, l, r);
            return;
        }
        push(node, l, r);
        int m = l + (r - l) / 2;
        update(node->left,  l,   m, ql, qr, updateTag);
        update(node->right, m+1, r, ql, qr, updateTag);
        pull(node);
    }

    Info query(Node* node, int l, int r, int ql, int qr) {
        if (!node || outside(l, r, ql, qr)) return Info();
        if (inside(l, r, ql, qr)) return node->info;
        push(node, l, r);
        int m = l + (r - l) / 2;
        Info leftRes  = query(node->left,  l,   m, ql, qr);
        Info rightRes = query(node->right, m+1, r, ql, qr);
        return leftRes + rightRes;
    }

public:
    /**
     * Construct over interval [left, right].
     */
    SparseSegTree(int left, int right)
      : root(nullptr), L(left), R(right) {}

    /** Range update: apply "updateTag" to all indices in [l, r]. */
    void range_update(int l, int r, const Tag &updateTag) {
        update(root, L, R, l, r, updateTag);
    }

    /** Range query: return aggregated Info over [l, r]. */
    Info range_query(int l, int r) {
        return query(root, L, R, l, r);
    }
};


enum UpdateType { ADD, SET, NONE };

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
	int sum = 0;

	/**
	 * Update the values of a node based on a lazy update.
	 * The lazy update will be "kept" on this node, so here we "fully" update it.
	 */
	void apply(const Tag &update, int l, int r) {
		if (update.type == SET) {
			sum = update.value * (r - l + 1);
		}
	}
};

/** @return result of joining nodes a and b together */
Info operator+(const Info &a, const Info &b) {
	return {a.sum + b.sum};
}

const int MAX = int(1e9);

void solve() {
    int m;
    cin >> m;

    int c = 0;
    SparseSegTree<Info,Tag> segtree(1, MAX);
    while (m--) {
        int di, xi, yi;
        cin >> di >> xi >> yi;
        if (di == 1) {
            Info res = segtree.range_query(xi + c, yi + c);
            c = res.sum;
            cout << res.sum << '\n';
        }
        else {
            assert(di == 2);
            segtree.range_update(xi + c, yi + c, Tag{SET, 1});
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

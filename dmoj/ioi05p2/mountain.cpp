#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
    using Pred = function<bool(const Info&)>;

    Node* root;
    ll L, R;

    // Check if [ql,qr] is completely outside [l,r]
    inline bool outside(ll l, ll r, ll ql, ll qr) {
        return qr < l || r < ql;
    }
    // Check if [l,r] is completely inside [ql,qr]
    inline bool inside(ll l, ll r, ll ql, ll qr) {
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
    void apply(Node* node, const Tag &update, ll l, ll r) {
        node->info.apply(update, l, r);
        node->lazy.apply(update);
        node->hasLazy = true;
    }

    // Push a pending update down to children
    void push(Node* node, ll l, ll r) {
        if (!node->hasLazy) return;
        ll m = l + (r - l) / 2;
        if (!node->left)  node->left  = new Node();
        if (!node->right) node->right = new Node();
        apply(node->left,  node->lazy, l,   m);
        apply(node->right, node->lazy, m+1, r);
        node->lazy    = Tag();
        node->hasLazy = false;
    }

    // Node*& is required because we change the pointer
    void update(Node* &node, ll l, ll r, ll ql, ll qr, const Tag &updateTag) {
        if (outside(l, r, ql, qr)) return;
        if (!node) node = new Node();
        if (inside(l, r, ql, qr)) {
            apply(node, updateTag, l, r);
            return;
        }
        push(node, l, r);
        ll m = l + (r - l) / 2;
        update(node->left,  l,   m, ql, qr, updateTag);
        update(node->right, m+1, r, ql, qr, updateTag);
        pull(node);
    }

    Info query(Node* node, ll l, ll r, ll ql, ll qr) {
        if (!node || outside(l, r, ql, qr)) return Info();
        if (inside(l, r, ql, qr)) return node->info;
        push(node, l, r);
        ll m = l + (r - l) / 2;
        Info leftRes  = query(node->left,  l,   m, ql, qr);
        Info rightRes = query(node->right, m+1, r, ql, qr);
        return leftRes + rightRes;
    }

    ll find_first(Node* node, ll l, ll r, const Info &acc, const Pred &pred) {
        if (!node) return R + 1;
        Info full = acc + node->info;
        if (!pred(full)) return R + 1;

        if (l == r) return l;

        push(node, l, r);
        ll m = l + (r - l) / 2;
        ll res = find_first(node->left, l, m, acc, pred);
        if (res != R + 1) return res;

        Info leftAcc = acc + (node->left ? node->left->info : Info());
        return find_first(node->right, m+1, r, leftAcc, pred);
    }
public:
    /**
     * Construct over interval [left, right].
     */
    SparseSegTree(ll left, ll right)
      : root(nullptr), L(left), R(right) {}

    /** Range update: apply "updateTag" to all indices in [l, r]. */
    void range_update(ll l, ll r, const Tag &updateTag) {
        update(root, L, R, l, r, updateTag);
    }

    /** Range query: return aggregated Info over [l, r]. */
    Info range_query(ll l, ll r) {
        return query(root, L, R, l, r);
    }

    /**
     * Find smallest value i in [L,R] such that predicate on prefix [L,i] holds.
     * Returns R + 1 if no such value.
     */
    ll find_first(const Pred& pred) {
        return find_first(root, L, R, Info(), pred);
    }
};

enum UpdateType { SET, NONE };

// Keeps track of Lazy Updates
struct Tag {
	// Default values
	UpdateType type = NONE;
	ll value = 0;

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
	ll sum = 0;
    ll prefix_max = 0;

	/**
	 * Update the values of a node based on a lazy update.
	 * The lazy update will be "kept" on this node, so here we "fully" update it.
	 */
	void apply(const Tag &update, ll l, ll r) {
		if (update.type == SET) {
			sum = update.value * (r - l + 1);
            prefix_max = max(ll(0), sum);
		}
	}
};

/** @return result of joining nodes a and b together */
Info operator+(const Info &a, const Info &b) {
    ll prefix_max = max(a.prefix_max, a.sum + b.prefix_max);
	return {a.sum + b.sum, prefix_max};
}

void solve() {
    int n;
    cin >> n;
    SparseSegTree<Info,Tag> segtree(0, n);
    while (1) {
        char c;
        cin >> c;
        if (c == 'I') {
            int a, b, d;
            cin >> a >> b >> d;
            segtree.range_update(a, b, Tag{SET, d});
        }
        else if (c == 'Q') {
            ll h;
            cin >> h;
            ll v = segtree.find_first([&](const Info &pref) {
                // find first larger: need to decrement after
                return pref.prefix_max > h;
            });
            v--;    // returns n + 1 in case there's nothing larger
            cout << v << '\n';
        }
        else {
            assert(c == 'E');
            break;
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

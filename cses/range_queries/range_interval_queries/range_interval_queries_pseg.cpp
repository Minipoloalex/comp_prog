#include <bits/stdc++.h>
using namespace std;

/**
 * Persistent segment tree (point update, range query)
 * - query on [l, r], 0-indexed
 * - needs: merge function f, identity iden
 * 
 * Usage:
 *  auto fsum = [](int64_t a, int64_t b) { return a + b; };
 *  persistent_segtree<int64_t,decltype(fsum)> st(n, fsum, 0, 22*n);
 *  vector<int> roots = {st.build(t)};
 *  vector<int> roots = {0};    // Or empty seg tree
 */
template<class T, class F>
struct persistent_segtree {
    struct Node { T val; int l, r; };
    int n;
    vector<Node> st;   // st[0] = null node: val=iden
    F f;
    T iden;

    persistent_segtree(int _n, F _f, T _iden, int reserve_nodes = 0)
        : n(_n), f(_f), iden(_iden) {
        st.reserve(max(1, reserve_nodes));
        st.push_back(Node{iden, 0, 0}); // neutral node: root 0 (use if you don't want to call build)
    }

    int new_node(const Node &x){ st.push_back(x); return int(st.size())-1; }
    int make_leaf(const T &v){ return new_node(Node{v, 0, 0}); }

    int build(int tl, int tr, const vector<T> &a){
        if (tl == tr) return make_leaf(a[tl]);
        int tm = (tl + tr) >> 1;
        int L = build(tl, tm, a), R = build(tm+1, tr, a);
        return new_node(Node{ f(st[L].val, st[R].val), L, R });
    }
    int update(int node, int tl, int tr, int pos, const T &val) {
        if (tl == tr) return make_leaf(val);
        int tm = (tl + tr) >> 1;
        int L = st[node].l, R = st[node].r;
        if (pos <= tm) L = update(L, tl, tm, pos, val);
        else           R = update(R, tm+1, tr, pos, val);
        return new_node(Node{ f(st[L].val, st[R].val), L, R });
    }
    T query(int node, int tl, int tr, int ql, int qr) const {
        if (qr < tl || tr < ql) return iden;
        if (ql <= tl && tr <= qr) return st[node].val;
        int tm = (tl + tr) >> 1;
        return f(query(st[node].l, tl, tm, ql, qr),
                 query(st[node].r, tm+1, tr, ql, qr));
    }

    // build from array: returns new root
    int build(const vector<T> &a){ return build(0, n-1, a); }

    // point update at "pos" (0-indexed): returns new root
    int update(int root, int pos, const T &val){ return update(root, 0, n-1, pos, val); }

    // range query on [ql, qr], 0-indexed
    T query(int root, int ql, int qr) const {
        return query(root, 0, n - 1, ql, qr);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
 	auto fsum = [](int a, int b) { return a + b; };
 	persistent_segtree<int,decltype(fsum)> st(n + 1, fsum, 0, 22*n);
 	vector<int> roots = {0};
	vector<int> vals = {0};
	vector<pair<int,int>> xs(n);
	for (int i = 0; i < n; i++) {
		auto &[xval, idx] = xs[i];
		cin >> xval;
		idx = i;
		vals.push_back(xval);
    }
	sort(xs.begin(), xs.end());
	for (int i = 0; i < n; ) {
		int cur_root = roots.back();
		int j;
		for (j = i; j < n && xs[j].first == xs[i].first; j++) {
			// we can do this, because there are no repetitions on same index
			// otherwise, we'd be setting multiple times to 1 instead of adding
			cur_root = st.update(cur_root, xs[j].second, 1);
		}
		i = j;
		roots.push_back(cur_root);
	}
	sort(vals.begin(), vals.end());
	vals.erase(unique(vals.begin(), vals.end()), vals.end());
	auto get_compressed_idx = [&](int val) {
		return int(upper_bound(vals.begin(), vals.end(), val) - vals.begin()) - 1;
	};
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
		a--;b--;
		int cidx = get_compressed_idx(c);
		int didx = get_compressed_idx(d);

		// if c is on the compressed list, we need to exclude it
		if (vals[cidx] == c) cidx--;

		int csum = st.query(roots[cidx], a, b);
		int dsum = st.query(roots[didx], a, b);
		int ans = dsum - csum;
        cout << ans << '\n';
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

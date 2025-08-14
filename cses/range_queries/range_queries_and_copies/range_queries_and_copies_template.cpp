#include <bits/stdc++.h>
using namespace std;

// Persistent segment tree (point update, range query)
// - query on [l, r], 0-indexed
// - needs: merge function f, identity iden
template<class T, class F>
struct persistent_segtree {
    struct Node { T val; int l, r; };
    int n;
    vector<Node> st;   // st[0] = null node: val=iden
    F f;
    T iden;

    persistent_segtree(int n, F f, T iden, int reserve_nodes = 0)
        : n(n), f(f), iden(iden) {
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
    vector<int64_t> t(n);
    for (auto &ti: t) cin >> ti;

    auto fsum = [&](int64_t a, int64_t b) { return a + b; };
    persistent_segtree<int64_t, decltype(fsum)> st(n, fsum, 0);

    vector<int> roots = {st.build(t)};
    while (q--) {
        int type, k;
        cin >> type >> k;
        k--;
        if (type == 1) {
            int a, x;
            cin >> a >> x;
            a--;
            roots[k] = st.update(roots[k], a, x);
        }
        else if (type == 2) {
            int a, b;
            cin >> a >> b;
            a--;b--;
            int64_t ans = st.query(roots[k], a, b);
            cout << ans << '\n';
        }
        else {
            assert(type == 3);
            roots.push_back(roots[k]);
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

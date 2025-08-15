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


struct T {
    int pref, suf, mx, sum;
    T(int p, int s, int m, int sm): pref(p), suf(s), mx(m), sum(sm) {}
    T(int v) {
        int positive = max(0, v);
        pref = positive;
        suf = positive;
        mx = positive;
        sum = v;
    }
};
T iden{0, 0, 0, 0};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    auto fmaxsubarray = [](const T &a, const T &b) {
        return T{
            max(a.pref, a.sum + b.pref),
            max(b.suf, a.suf + b.sum),
            max({a.mx, b.mx, a.suf + b.pref}),
            a.sum + b.sum
        };
    };
    persistent_segtree<T,decltype(fmaxsubarray)> st(m, fmaxsubarray, iden, 22*n);
    vector<int> roots = {0};
    vector<vector<pair<int,int>>> vs(n);
    for (int i = 0; i < k; i++) {
        int ri, ci, vi;
        cin >> ri >> ci >> vi;
        ri--;ci--;
        vs[ri].emplace_back(ci, vi);
    }
    vector<int> colsum(m);
    for (int r = 0; r < n; r++) {
        int cur_root = roots.back();
        for (auto &[c, v]: vs[r]) {
            colsum[c] += v;
            cur_root = st.update(cur_root, c, T(colsum[c]));
        }
        roots.push_back(cur_root);
    }
    int q;
    cin >> q;
    array<int,3> as = {0, 0, 0};
    while (q--) {
        int qhj, qxj, qyj;
        cin >> qhj >> qxj >> qyj;
        int hj = qhj ^ as[0];
        int xj = qxj ^ as[1];
        int yj = qyj ^ as[2];
        // cout << hj << " " << xj << " " << yj << endl;

        xj--;   // 1-indexed
        yj--;
        T res = st.query(roots[hj], xj, yj);
        cout << res.mx << '\n';
        as[0] = as[1];
        as[1] = as[2];
        as[2] = res.mx;
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

#include <bits/stdc++.h>
using namespace std;

// Tested on:
// - CSES/Range-Queries-and-Copies

/**
 * Persistent segment tree (point update, range query)
 * - query on [l, r], 0-indexed
 * - needs: merge function f, identity iden
 * 
 * Usage:
 *  auto fsum = [](int64_t a, int64_t b) { return a + b; };
 *  persistent_segtree<int64_t,decltype(fsum)> st(n, fsum, 0);
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
    // A and B refer to the history/time: for answering queries
    // Left and right refer to the segment tree array (as usual)
    template<class Pred>
    int find_first(int nodeA, int nodeB, int tl, int tr, const T &accA, const T &accB, const Pred &pred) {
        if (!pred(f(accA, st[nodeA].val), f(accB, st[nodeB].val))) {
            return -1;
        }
        if (tl == tr) return tl;
        int tm = (tl + tr) >> 1;
        int aL = st[nodeA].l, aR = st[nodeA].r;
        int bL = st[nodeB].l, bR = st[nodeB].r;
        T leftA = f(accA, st[aL].val);
        T leftB = f(accB, st[bL].val);

        // If the predicate is already valid on left, go left
        if (pred(leftA, leftB)) {
            return find_first(aL, bL, tl, tm, accA, accB, pred);
        }
        // Otherwise, go right and carry the left values into the accumulators
        return find_first(aR, bR, tm + 1, tr, leftA, leftB, pred);
    }

    // build from array: returns new root
    int build(const vector<T> &a){ return build(0, n-1, a); }

    // point update at "pos" (0-indexed): returns new root
    int update(int root, int pos, const T &val){ return update(root, 0, n-1, pos, val); }

    // range query on [ql, qr], 0-indexed
    T query(int root, int ql, int qr) const {
        return query(root, 0, n - 1, ql, qr);
    }

    /**
     * Walk on two segment trees at the same time.
     * @return i corresponding to the smallest prefix [0,i] where pred is True. 
     * -1 if pred is always False
     */
    template<class Pred>
    int find_first(int left_root, int right_root, const Pred &pred) {
        return find_first(left_root, right_root, 0, n - 1, iden, iden, pred);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> sorteda = a;
    sort(sorteda.begin(), sorteda.end());
    // distinct integer numbers, so we don't need to do unique
    auto get_idx = [&](int v) {
        return int(lower_bound(sorteda.begin(), sorteda.end(), v) - sorteda.begin());
    };

    auto fsum = [](int v1, int v2) { return v1 + v2; };
    persistent_segtree<int, decltype(fsum)> st(n, fsum, 0, 22*n);
    vector<int> roots = {0};
    for (int i = 0; i < n; i++) {
        int v = a[i];
        int compressed_idx = get_idx(v);
        roots.push_back(st.update(roots.back(), compressed_idx, +1));
    }
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        int lo = st.find_first(roots[l - 1], roots[r], [k](int cntleft, int cntright) {
            return cntright - cntleft >= k;
        });
        assert(lo != -1);
        int ans = sorteda[lo];
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

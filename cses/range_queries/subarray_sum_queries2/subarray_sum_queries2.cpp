#include <bits/stdc++.h>
using namespace std;

// point update, range query; 0-indexed
// supports non-commutative functions
template <typename T>
struct seg_tree {
    // Neutral element: inf in min seg_tree, 0 in sum seg_tree, ...
    const T iden;

    int n;
    vector<T> t;

    // Round n to the next power of 2
    seg_tree(int sz) : n(1 << int(ceil(log2(sz)))), t(2 * n, iden) {}

    // Constructor from array
    seg_tree(const vector<T>& v) :
        n(1 << int(ceil(log2(v.size())))),
        t(2 * n, iden) {
        for (int i = 0; i < int(v.size()); i++) {
            update(i, v[i]);
        }
    }

    T f(const T& l, const T& r) {
        return T::combine(l, r);
    }

    // Point update in position p, 0-indexed
    void update(int p, T val) {
        t[p += n] = val;
        for (p >>= 1; p > 0; p >>= 1)
            t[p] = f(t[p << 1], t[p << 1 | 1]);
    }

    // Range [l, r); Keeps left and right results separate for non-commutative f
    T query(int l, int r) {
        T l_res = iden, r_res = iden;

        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            // if l is odd, then l is a right child and this interval is contained in the result
            if (l & 1) l_res = f(l_res, t[l++]);

            // if r is odd, then r - 1 is a left child contained in the result
            if (r & 1) r_res = f(t[--r], r_res);
        }

        return f(l_res, r_res);
    }
};

struct T {
    int64_t pref = 0, suf = 0, mx = 0, sum = 0;
    static T combine(T const&l, T const&r) {
        return {max(l.pref, l.sum + r.pref), max(r.suf, r.sum + l.suf), max({l.mx, r.mx, l.suf + r.pref}), l.sum + r.sum};
    }
    static T single(int val) {
        return {max(0, val), max(0, val), max(0, val), val};
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<T> x(n);
    for (auto &xi: x) {
        int xval; cin >> xval;
        xi = T::single(xval);
    }
    seg_tree<T> st(x);
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;r--;
        T res = st.query(l, r + 1); // [l, r)
        cout << res.mx << '\n';
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

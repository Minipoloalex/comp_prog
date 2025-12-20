#include <bits/stdc++.h>
using namespace std;

struct Node {
    int mn, mx, ans;
    bool operator==(const Node &o) const {
        return make_tuple(mn,mx,ans) == make_tuple(o.mn,o.mx,o.ans);
    }
};

// point update, range query; 0-indexed
// supports non-commutative functions
template <typename T>
struct seg_tree {
    // Neutral element: inf in min seg_tree, 0 in sum seg_tree, ...
    T iden;

    using F = function<T(T,T)>;
    F f;

    int n;
    vector<T> t;

    // Constructor from array
    seg_tree(const vector<T>& v, T const& _iden, F const& _f) :
        iden(_iden),
        f(_f),
        n(1 << int(ceil(log2(v.size())))),
        t(2 * n, iden) {
        for (int i = 0; i < int(v.size()); i++) {
            update(i, v[i]);
        }
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

    // Returns the first index i where arr[i] >= val, in max seg tree, or -1 if it does not exist
    // Can be adapted to similar 'walk' queries in min and sum seg trees
    int walk(T val) {
        int p = 1;
        if (t[p] < val) return -1; // no element >= val
        while (p < n) {
            if (t[p << 1] >= val) p = p << 1;
            else p = p << 1 | 1;
        }
        return p - n;
    }
};

Node iden = {INT_MAX, INT_MIN, INT_MIN};

Node comb_mM(Node l, Node r) {
    if (l == iden) return r;
    if (r == iden) return l;
    return {min(l.mn,r.mn), max(l.mx,r.mx), max({l.ans, r.ans, r.mx - l.mn})};
}

Node comb_Mm(Node l, Node r) {
    if (l == iden) return r;
    if (r == iden) return l;
    return {min(l.mn,r.mn), max(l.mx,r.mx), max({l.ans, r.ans, l.mx - r.mn})};
}
Node single_mM(int i, int x) {
    return Node{x-i,x-i,0};
}
Node single_Mm(int i, int x) {
    return Node{x+i,x+i,0};
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<Node> a_mM(n), a_Mm(n);
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a_mM[i] = single_mM(i, ai);
        a_Mm[i] = single_Mm(i, ai);
    }
    seg_tree<Node> st_mM(a_mM, iden, comb_mM);
    seg_tree<Node> st_Mm(a_Mm, iden, comb_Mm);
    auto get_ans = [&]() -> int {
        return max(st_mM.query(0,n).ans, st_Mm.query(0,n).ans);
    };
    auto upd = [&](int i, int x) {
        st_mM.update(i, single_mM(i, x));
        st_Mm.update(i, single_Mm(i, x));
    };
    cout << get_ans() << '\n';
    while (q--) {
        int p, x;
        cin >> p >> x;
        p--;
        upd(p,x);
        cout << get_ans() << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

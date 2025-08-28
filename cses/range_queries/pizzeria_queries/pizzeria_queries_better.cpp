#include <bits/stdc++.h>
using namespace std;

// point update, range query; 0-indexed
// supports non-commutative functions
template <typename T>
struct seg_tree {
    // Neutral element: inf in min seg_tree, 0 in sum seg_tree, ...
    const T iden = numeric_limits<T>::max();

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
        return min(l, r);
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

void solve() {
    // I think this is a more elegant solution
    int n, q;
    cin >> n >> q;
    vector<int> p(n);
    for (auto &pi: p) cin >> pi;
    vector<int> lefvals(n), rigvals(n);
    for (int i = 0; i < n; i++) {
        lefvals[i] = p[i] - i;
        rigvals[i] = p[i] + i;
    }
    seg_tree<int> stleft(lefvals), stright(rigvals);
    auto update = [&](int idx, int new_pizza_cost) {
        stleft.update(idx, new_pizza_cost - idx);
        stright.update(idx, new_pizza_cost + idx);
    };
    auto get = [&](int idx) {
        int mn = min(stleft.query(0, idx) + idx, stright.query(idx, n) - idx);
        return mn;
    };
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, x;
            cin >> k >> x;
            k--;
            update(k, x);
        }
        else {
            assert(t == 2);
            int k;
            cin >> k;
            k--;
            cout << get(k) << '\n';  
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

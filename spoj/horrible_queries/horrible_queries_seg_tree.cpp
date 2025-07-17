#include <bits/stdc++.h>
using namespace std;


#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)

typedef int64_t T;
const T iden = 0;

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 */
class LazySegmentTree {
private:
    T default_value = iden;
// private:
public:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts "elements" artificially added)

    vector<T> st;

    // represents lazy updates (updates that are already complete for the current node, but not for the children)
    vector<T> lz;

    T f(const T &a, const T &b) {
        return a + b;
    }
    /** All indices are inclusive */
    bool outside(int l, int r, int i, int j) {
        return j < l || r < i;
    }
    /** All indices are inclusive */
    bool inside(int l, int r, int i, int j) {
        return i <= l && r <= j;
    }
    /** applies lazy update to st[current], places update at lz[current] */
    void apply_lazy(int current, int l, int r, T add) {
        int len = r - l + 1;
        st[current] += add * len;
        lz[current] += add;
    }
    /** pushes down lazy updates to children of node current */
    void push_down(int current, int l, int r) {
        int m = (l + r) / 2;
        int leftC = lc(current);
        int rightC = rc(current);
        apply_lazy(leftC, l, m, lz[current]);
        apply_lazy(rightC, m + 1, r, lz[current]);
        lz[current] = iden;
    }
    void range_add(int i, int j, int current, int l, int r, T add) {
        if (outside(l, r, i, j)) return;
        if (inside(l, r, i, j)) {
            apply_lazy(current, l, r, add);
            return;
        }

        // partially inside

        // update children's values with previous lazy updates
        push_down(current, l, r);

        int m = (l + r) / 2;
        int leftC = lc(current);
        int rightC = rc(current);
        range_add(i, j, leftC, l, m, add);
        range_add(i, j, rightC, m + 1, r, add);
        st[current] = f(st[leftC], st[rightC]);
    }
    T range_query(int i, int j, int current, int l, int r) {
        if (outside(l, r, i, j)) return iden;
        if (inside(l, r, i, j)) {
            return st[current];
        }
        push_down(current, l, r);
        int m = (l + r) / 2;
        int leftC = lc(current);
        int rightC = rc(current);
        T rl = range_query(i, j, leftC, l, m);
        T rr = range_query(i, j, rightC, m + 1, r);
        return f(rl, rr);
    }
public:
    LazySegmentTree(int _n) {
        size = 1;
        while (size < _n) size <<= 1;
        n = size;
        size <<= 1;

        // do not need to set this here: could be 0
        // the get function will return the default value
        st.assign(size, default_value);
        lz.assign(size, default_value);
    }

    /** @return sum of values on [i, j] (0-indexed) */
    T range_query(int i, int j) {
        return range_query(i, j, 1, 0, n - 1);
    }

    /** adds to every value on the range [i, j] (0-indexed) */
    void range_add(int i, int j, T add) {
        range_add(i, j, 1, 0, n - 1, add);
    }
};

void solve() {
    int n, c;
    cin >> n >> c;
    LazySegmentTree st(n);
    while (c--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p, q, v;
            cin >> p >> q >> v;
            p--;q--;
            st.range_add(p,q,v);
        }
        else {
            int p, q;
            cin >> p >> q;
            p--;q--;
            int64_t ans = st.range_query(p,q);
            cout << ans << '\n';
        }
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

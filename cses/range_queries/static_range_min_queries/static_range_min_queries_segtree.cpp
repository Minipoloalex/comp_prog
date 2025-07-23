#include <bits/stdc++.h>
using namespace std;

#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)

#define item int
const item DEFAULT = int(1e9);

class SegTree {
public:
    int size, n;
    vector<item> st;
    item combine(item lr, item rr) {
        return min(lr, rr);
    }

    bool outside(int i, int j, int l, int r) {
        // i j l r
        // l r i j
        return j < l || i > r;
    }
    bool inside(int l, int r, int i, int j) {
        // i l r j
        return l >= i && r <= j;
    }
    item get(int i, int j, int l, int r, int curr) {
        if (outside(i, j, l, r)) {
            return DEFAULT;
        }
        if (inside(l, r, i, j)) {
            return st.at(curr);
        }

        int m = (l + r) / 2;
        item lr = get(i, j, l, m, lc(curr));
        item rr = get(i, j, m + 1, r, rc(curr));
        return combine(lr, rr);
    }
    void build(vector<int> &v, int l, int r, int curr) {
        if (l == r) {
            st.at(curr) = v.at(l);
            return;
        }
        int m = (l + r) / 2;
        int left_child = lc(curr), right_child = rc(curr);
        build(v, l, m, left_child);
        build(v, m + 1, r, right_child);

        st[curr] = combine(st.at(left_child), st.at(right_child));
    }
public:
    SegTree(int _n): n(_n) {
        size = _n * 4;
        st.assign(size, DEFAULT);
    }
    void build(vector<int> &v) {
        build(v, 0, n - 1, 1);
    }
    int get(int a, int b) {
        return get(a, b, 0, n - 1, 1);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (auto &x: v) cin >> x;
    SegTree st(n);
    st.build(v);

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << st.get(a, b) << '\n';
    }
    return 0;
}

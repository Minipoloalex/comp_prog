#include <bits/stdc++.h>
using namespace std;

#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)

class SegTree {
    vector<int64_t> st;
    int n, sz;
    const int64_t DEFAULT = 0;
    int64_t combine(int64_t a, int64_t b) {
        return a + b;
    }
    bool outside(int i, int j, int l, int r) {
        return l > j || r < i;
    }
    bool inside(int i, int j, int l, int r) {
        return l >= i && r <= j;
    }
    void build(int cur, int l, int r, vector<int> &a) {
        if (l == r) {
            st[cur] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(lc(cur), l, m, a);
        build(rc(cur), m + 1, r, a);
        st[cur] = combine(st[lc(cur)], st[rc(cur)]);
    }
    int64_t get(int i, int j, int cur, int l, int r) {
        if (outside(i, j, l, r)) {
            return DEFAULT;
        }
        if (inside(i, j, l, r)) return st[cur];

        int m = (l + r) / 2;
        int64_t rl = get(i, j, lc(cur), l, m);
        int64_t rr = get(i, j, rc(cur), m + 1, r);
        return combine(rl, rr);
    }
    void update(int cur, int l, int r, int i, int v) {
        if (outside(i, i, l, r)) return;
        if (l == r) {
            st[cur] = v;
            return;
        }
        int m = (l + r) / 2;
        update(lc(cur), l, m, i, v);
        update(rc(cur), m + 1, r, i, v);
        st[cur] = combine(st[lc(cur)], st[rc(cur)]);
    }
public:
    SegTree(int nn) {
        n = nn;
        sz = 4 * n;
        st.assign(sz, DEFAULT);
    }
    int64_t get(int i, int j) {
        return get(i, j, 1, 0, n - 1);
    }
    void build(vector<int> &a) {
        build(1, 0, n - 1, a);
    }
    void update(int i, int v) {
        update(1, 0, n - 1, i, v);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    SegTree st(n);
    st.build(x);
    while (q--) {
        int typ;
        cin >> typ;
        if (typ == 1) {
            int k, u;
            cin >> k >> u;
            st.update(k - 1, u);
        }
        else {
            assert(typ == 2);
            int a, b;
            cin >> a >> b;
            cout << st.get(a - 1, b - 1) << '\n';
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

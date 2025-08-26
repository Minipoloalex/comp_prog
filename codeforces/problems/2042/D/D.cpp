#include <bits/stdc++.h>
using namespace std;

// point update, range query; 0-indexed
// supports non-commutative functions
template <typename T>
struct seg_tree {
    // Neutral element: inf in min seg_tree, 0 in sum seg_tree, ...
    const T iden = numeric_limits<T>::min();

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
        return max(l, r);
    }

    // Point update in position p, 0-indexed
    void update(int p, T val) {
        p += n;
        t[p] = f(t[p], val);
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

typedef array<int,3> T;

void solve() {
    int n;
    cin >> n;
    vector<int> vals;
    vector<T> segs(n);
    for (int i = 0; i < n; i++) {
        auto &[l, r, origidx] = segs[i];
        cin >> l >> r;
        vals.push_back(r);
        origidx = i;
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto get_compressed_idx = [&](int val) {
        return int(lower_bound(vals.begin(), vals.end(), val) - vals.begin());
    };
    sort(segs.begin(), segs.end(), [](T &a, T &b) {
        // ascending L, descending R
        return make_tuple(a[0], -a[1]) < make_tuple(b[0], -b[1]);
    });

    // We actually don't need to do this with a segment tree
    // We can just use the set lower_bound approach for both sides:
    // first sort by L, and calculate rj - ri
    // then sort by R descending, and calculate li - lj
    seg_tree<int> st(n);
    set<int> rs;
    auto insert = [&](int idx) {
        auto &[l, r, origidx] = segs[idx];
        rs.insert(r);
        int ridx = get_compressed_idx(r);
        st.update(ridx, l);
    };
    vector<int> ans(n);
    insert(0);
    for (int i = 1; i < n; insert(i), i++) {
        auto &[l, r, origidx] = segs[i];
        if (i + 1 < n) {
            if (segs[i + 1][0] == l && segs[i + 1][1] == r) {
                ans[origidx] = 0;
                continue;
            }
        }
        auto it = rs.lower_bound(r);
        if (it != rs.end()) {
            int rj = *it;
            int rj_compressed = get_compressed_idx(rj);
            int lj = st.query(rj_compressed, n);
            assert(lj != INT_MIN);

            ans[origidx] = rj - r + l - lj;
        }
        else {
            ans[origidx] = 0;
        }
    }
    for (int v: ans) cout << v << '\n';
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

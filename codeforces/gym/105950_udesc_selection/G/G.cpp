#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

typedef array<array<int64_t,2>,2> MAT;
const MAT matid = {array<int64_t,2>{1,0}, array<int64_t,2>{0,1}};

MAT matprod(const MAT &a, const MAT &b) {
    MAT ans;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int64_t v = 0;
            for (int k = 0; k < 2; k++) {
                v = (v + a[i][k] * b[k][j]) % MOD;
            }
            ans[i][j] = v;
        }
    }
    return ans;
}

struct T {
    array<MAT,2> mats;
    int idx;
};

const T iden = {{matid, matid}, 0};

/**
 * Represents the type of lazy update being done.
 * NONE = if there's no lazy update to be performed
 */
enum LazyUpdateType { INVERT, NONE };

struct LazyUpdate {
    LazyUpdateType type;
};

const LazyUpdate update_iden = LazyUpdate{NONE};

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 */
class LazySegmentTree {
private:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts "elements" artificially added)

    vector<T> st;

    // represents lazy updates (updates that are already complete for the current node, but not for the children)
    vector<LazyUpdate> lz;

    T f(const T &a, const T &b) {
        const MAT &A = a.mats[a.idx];      // segment [L..M] (left)
        const MAT &B = b.mats[b.idx];      // segment [M+1..R] (right)
        const MAT &cur = matprod(B, A);   // apply first A, then B (because we are combining matrices!)
        const MAT &other = matprod(b.mats[1-b.idx], a.mats[1-a.idx]);
        return {{cur, other}, 0};
    }
    /** applies lazy update to st[current], places update at lz[current] */
    void apply_lazy(int current, int l, int r, const LazyUpdate &update) {
        if (update.type == INVERT) {
            st[current].idx = 1 - st[current].idx;
            if (lz[current].type == INVERT) {
                lz[current].type = NONE;
            }
            else {
                lz[current].type = INVERT;
            }
        }
    }

    inline int lc(int i) { return i * 2; }
    inline int rc(int i) { return i * 2 + 1; }

    /** All indices are inclusive */
    bool outside(int l, int r, int i, int j) {
        return j < l || r < i;
    }
    /** All indices are inclusive */
    bool inside(int l, int r, int i, int j) {
        return i <= l && r <= j;
    }
    void build(int current, int l, int r, const vector<T> &a) {
        if (l >= int(a.size())) return;
        if (l == r) {
			st[current] = a[l];
		}
        else {
			int m = (l + r) / 2;
            int leftC = lc(current);
            int rightC = rc(current);
            build(leftC, l, m, a);
            build(rightC, m + 1, r, a);
			st[current] = f(st[leftC], st[rightC]);
		}
	}
    /** pushes down lazy updates to children of node current */
    void push_down(int current, int l, int r) {
        int m = (l + r) / 2;
        int leftC = lc(current);
        int rightC = rc(current);
        apply_lazy(leftC, l, m, lz[current]);
        apply_lazy(rightC, m + 1, r, lz[current]);
        lz[current] = update_iden;
    }

    // handles both range_set and range_add
    void range_update(int i, int j, int current, int l, int r, LazyUpdate update) {
        if (outside(l, r, i, j)) return;
        if (inside(l, r, i, j)) {
            apply_lazy(current, l, r, update);
            return;
        }
        // partially inside

        // update children's values with previous lazy updates
        push_down(current, l, r);

        int m = (l + r) / 2;
        int leftC = lc(current);
        int rightC = rc(current);
        range_update(i, j, leftC, l, m, update);
        range_update(i, j, rightC, m + 1, r, update);
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

        st.assign(size, iden);
        lz.assign(size, update_iden);
    }
    LazySegmentTree(const vector<T> &a) : LazySegmentTree(int(a.size())) {
        build(a);
    }
    void build(const vector<T> &a) {
        build(1, 0, n - 1, a);
    }

    /** @return sum of values on [i, j] (0-indexed) */
    T range_query(int i, int j) {
        return range_query(i, j, 1, 0, n - 1);
    }
    void range_invert(int i, int j) {
        range_update(i, j, 1, 0, n - 1, LazyUpdate{INVERT});
    }
};

MAT mat0 = {array<int64_t,2>{1, 1}, array<int64_t,2>{0, 1}};
MAT mat1 = {array<int64_t,2>{1, 1}, array<int64_t,2>{1, 0}};
array<MAT,2> basic_matrices = {mat0, mat1};

void solve() {
    int n;
    int64_t a, b;
    cin >> n >> a >> b;
    if (a < b) swap(a, b);
    string s;
    cin >> s;
    vector<T> arr(n);
    for (int i = 0; i < n; i++) {
        int c = s[i] - '0';
        arr[i] = {basic_matrices[c], basic_matrices[1 - c], 0};
    }
    LazySegmentTree st(arr);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;r--;
        st.range_invert(l, r);
        T result = st.range_query(0, n - 1);
        MAT cur = result.mats[result.idx];
        int64_t x = (cur[0][0] * a % MOD + cur[0][1] * b % MOD) % MOD;
        cout << x << '\n';
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

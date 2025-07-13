#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;


#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)

typedef pair<int64_t,int64_t> T;
const T iden = {1, 0};

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 */
class SegmentTree {
private:
    T default_value = iden;
// private:
public:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts additionally added)
    vector<T> st;
    T f(const T& a, const T& b) {
        auto &[ca, da] = a;
        auto &[cb, db] = b;
        return {cb * ca % MOD, (cb * da + db) % MOD};
    }
    /**
     * @brief All indices are inclusive
     */
    bool outside(int l, int r, int i, int j) {
        return j < l || r < i;
    }
    /**
     * @brief All indices are inclusive
     */
    bool inside(int l, int r, int i, int j) {
        return i <= l && r <= j;
    }

    /**
     * @brief 
     * 
     * @param i Index of the starting array to set. Does not correspond to the node's index.
     * Instead corresponds to the node's limits.
     * @param value Value to set node with limits [i, i]
     * @param current Current node index
     * @param l Current node's left limit
     * @param r Current node's right limit
     */
    void update(int i, T value, int current, int l, int r) {
        if (outside(l, r, i, i)) return;
        if (l == r) {
            st[current] = value;
            return;
        }
        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        update(i, value, leftC, l, m);
        update(i, value, rightC, m + 1, r);
        st[current] = f(st[leftC], st[rightC]);
    }

    T get(int i, int j, int current, int l, int r) {
        if (outside(l, r, i, j)) return iden;
        if (inside(l, r, i, j)) return st[current];

        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        T rl = get(i, j, leftC, l, m);
        T rr = get(i, j, rightC, m + 1, r);
        return f(rl, rr);
    }
public:
    SegmentTree(int _n) {
        size = 1;
        while (size < _n) size <<= 1;
        n = size;
        size <<= 1;

        // do not need to set this here: could be 0
        // the get function will return the default value
        st.assign(size, default_value);
    }
    SegmentTree(const vector<T> &arr) : SegmentTree(int(arr.size())) {
        for (int i = 0; i < int(arr.size()); i++) { // use arr.size(), not n
            update(i, arr[i]);
        }
    }

    // 0-indexed
    void update(int i, T value) {
        update(i, value, 1, 0, n - 1);
    }

    // 0-indexed: [i, j]
    T get(int i, int j) {
        return get(i, j, 1, 0, n - 1);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<T> f(n);
    for (auto &[c, d]: f) cin >> c >> d;
    SegmentTree st(f);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p, c, d;
            cin >> p >> c >> d;
            st.update(p, {c, d});
        }
        else {
            assert(type == 1);
            int l, r, x;
            cin >> l >> r >> x;
            auto [c, d] = st.get(l, r-1);
            int64_t ans = (c * x + d) % MOD;
            cout << ans << '\n';
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

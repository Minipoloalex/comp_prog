#include <bits/stdc++.h>
using namespace std;


#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)

typedef struct {
    int64_t pref, suf, sm, mx;
} T;
const T iden = {0,0,0,0};

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 */
class SegmentTreeMaxSubarraySum {
private:
    T default_value = iden;
// private:
public:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts additionally added)
    vector<T> st;
    T f(const T &a, const T &b) {
        T ans;
        ans.mx = max(a.mx, b.mx);
        ans.mx = max(ans.mx, a.suf + b.pref);

        ans.pref = max(a.pref, a.sm + b.pref);
        ans.suf = max(b.suf, b.sm + a.suf);
        ans.sm = a.sm + b.sm;
        return ans;
    }
    T single(int a) {
        if (a < 0) return {0, 0, a, 0};
        return {a, a, a, a};
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
    void update(int i, const T &value, int current, int l, int r) {
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
    SegmentTreeMaxSubarraySum(int _n) {
        size = 1;
        while (size < _n) size <<= 1;
        n = size;
        size <<= 1;

        // do not need to set this here: could be 0
        // the get function will return the default value
        st.assign(size, default_value);
    }
    SegmentTreeMaxSubarraySum(const vector<int> &arr) : SegmentTreeMaxSubarraySum(int(arr.size())) {
        for (int i = 0; i < int(arr.size()); i++) {
            update(i, single(arr[i]));
        }
    }

    // 0-indexed
    void update(int i, T value) {
        update(i, value, 1, 0, n - 1);
    }
    void update(int i, int value) {
        update(i, single(value), 1, 0, n - 1);
    }

    // 0-indexed: [i, j]
    T get(int i, int j) {
        return get(i, j, 1, 0, n - 1);
    }
};


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    SegmentTreeMaxSubarraySum st(x);
    while (m--) {
        int k, xnew;
        cin >> k >> xnew;
        k--;
        st.update(k, xnew);
        T ans = st.get(0, n - 1);
        cout << ans.mx << '\n';
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

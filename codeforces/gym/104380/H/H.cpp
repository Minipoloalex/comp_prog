#include <bits/stdc++.h>
using namespace std;


#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)
// #define p(i) ((i) / 2)

typedef array<int,3> T;    // {MAX, first_max_id}
const T iden = {0, 0, 0};
const T value_0 = {0, 1, 0};
const T value_1 = {1, 0, 0};

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
    T f(const T &a, const T &b) {
        auto &[p1, s1, c1] = a;
        auto &[p2, s2, c2] = b;
        int mn = min(s1, p2);
        return {p1 + (p2 - mn), s2 + (s1 - mn), c1 + c2 + mn};
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
    string s;
    cin >> s;
    int n = int(s.size());
    SegmentTree st(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            st.update(i, value_0);
        }
        else {
            st.update(i, value_1);
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        if (k == 1) {
            int x;
            cin >> x;
            int i = x - 1;
            if (s[i] == '0') {
                s[i] = '1';
                st.update(i, value_1);
            }
            else {
                assert(s[i] == '1');
                s[i] = '0';
                st.update(i, value_0);
            }
        }
        else {
            assert(k == 2);
            int l, r;
            cin >> l >> r;
            l--;r--;
            auto [ones, zeros, combineds] = st.get(l, r);
            int sz = r - l + 1;
            assert(sz - 2 * combineds == ones + zeros);
            cout << ones + zeros << '\n';
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

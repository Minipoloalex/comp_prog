#include <bits/stdc++.h>
using namespace std;

#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)
// #define p(i) ((i) / 2)

typedef int64_t ll;
typedef int64_t item;

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 * 
 */
class SegmentTree {
private:
    item NEUTRAL_ELEMENT = 0;    // EMPTY SEGMENT

    item combine(item a, item b) {
        return a | b;
    }
    inline item single(int a) {
        return 1LL << a;
    }
// private:
public:
    int64_t size;   // 2 * n (size of the segment tree array)
    int64_t n;      // size of the "original" array (counts additionally added)

    vector<item> st;    // sets always small: size <= 40 (1 <= ai <= 40) -> merging in ≃ O(1)
    /**
     * @brief All indices are inclusive
     * 
     * @param i 
     * @param j 
     * @param l 
     * @param r 
     * @return true 
     * @return false 
     */
    bool outside(int64_t l, int64_t r, int64_t i, int64_t j) {
        return j < l || r < i;
    }
    /**
     * @brief All indices are inclusive
     * 
     * @param i 
     * @param j 
     * @param l 
     * @param r 
     * @return true 
     * @return false 
     */
    bool inside(int64_t l, int64_t r, int64_t i, int64_t j) {
        return i <= l && r <= j;
    }
    void build(vector<int> &items, int64_t current, int64_t l, int64_t r) {
        if (l == r) {
            if (l < (int64_t) items.size()) st.at(current) = single(items.at(l));
            else st.at(current) = NEUTRAL_ELEMENT;
            return;
        }
        int64_t leftC = lc(current);
        int64_t rightC = rc(current);
        int64_t m = (l + r) / 2;

        build(items, leftC, l, m);
        build(items, rightC, m + 1, r);
        st.at(current) = combine(st.at(leftC), st.at(rightC));
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
    void update(int64_t i, int value, int64_t current, int64_t l, int64_t r) {
        if (outside(l, r, i, i)) return;
        if (l == r) {
            st.at(current) = single(value);
            return;
        }
        int64_t leftC = lc(current);
        int64_t rightC = rc(current);
        int64_t m = (l + r) / 2;

        update(i, value, leftC, l, m);
        update(i, value, rightC, m + 1, r);
        st.at(current) = combine(st.at(leftC), st.at(rightC));
    }

    item get(int64_t i, int64_t j, int64_t current, int64_t l, int64_t r) {
        if (outside(l, r, i, j)) return NEUTRAL_ELEMENT;
        if (inside(l, r, i, j)) return st.at(current);

        int64_t leftC = lc(current);
        int64_t rightC = rc(current);
        int64_t m = (l + r) / 2;

        auto rl = get(i, j, leftC, l, m);
        auto rr = get(i, j, rightC, m + 1, r);
        return combine(rl, rr);
    }

public:
    SegmentTree(int _n) {
        size = 1;
        while (size < _n) size <<= 1;
        n = size;
        size <<= 1;

        // do not need to set this here: we can just not assign anything
        // the get function will return the default value
        // st.assign(size, make_pair(INT_MAX, 0));
        st.resize(size);
    }
    /**
     * @brief
     * 
     * @param i 0-indexed
     * @param value 
     */
    void update(int64_t i, int value) {
        update(i, value, 1, 0, n - 1);
    }
    /**
     * @brief 
     * 
     * @param i 
     * @param j 
     */
    item get(int64_t i, int64_t j) {
        return get(i, j, 1, 0, n - 1);
    }
    void build(vector<int> &items) {
        build(items, 1, 0, n - 1);
    }
};

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    SegmentTree st(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    st.build(a);

    while (q--) {
        int op, xi, yi;
        cin >> op >> xi >> yi;
        if (op == 1) {
            item res = st.get(xi - 1, yi - 1);
            int ans = 0;
            while (res) {
                res -= (res & -res);
                ans++;
            }
            cout << ans << '\n';
        }
        else {
            assert(op == 2);
            st.update(xi - 1, yi);
        }
    }
    return 0;
}

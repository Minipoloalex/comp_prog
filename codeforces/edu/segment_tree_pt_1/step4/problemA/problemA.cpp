#include <bits/stdc++.h>
using namespace std;

#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)
// #define p(i) ((i) / 2)

typedef int64_t ll;
typedef ll item;
// struct item {
//     ll seg, pref, suf, sum;
// };

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 * 
 */
class SegmentTree {
private:
    item NEUTRAL_ELEMENT = 0;    // EMPTY SEGMENT

    item single(int64_t v, int64_t i) {
        return (i % 2 == 0) ? v : -v;
    }
    item combine(item &a, item &b) {
        return a + b;
    }
// private:
public:
    int64_t size;   // 2 * n (size of the segment tree array)
    int64_t n;      // size of the "original" array (counts additionally added)
    vector<item> st;
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
    void update(int64_t i, int64_t value, int64_t current, int64_t l, int64_t r) {
        if (outside(l, r, i, i)) return;
        if (l == r) {
            st.at(current) = single(value, l);
            return;
        }
        int64_t leftC = lc(current);
        int64_t rightC = rc(current);
        int64_t m = (l + r) / 2;

        update(i, value, leftC, l, m);
        update(i, value, rightC, m + 1, r);
        st.at(current) = combine(st.at(leftC), st.at(rightC));
    }

    item modified_get(int64_t i, int64_t j, int64_t current, int64_t l, int64_t r, bool even_starts) {
        if (outside(l, r, i, j)) return NEUTRAL_ELEMENT;
        if (inside(l, r, i, j)) {
            int64_t value = st.at(current);
            // cout << i << " " << j << " " << current << " " << l << " " << r << " " << boolalpha << even_starts << " " << (l % 2 == 0 && even_starts) << " " << (l % 2 == 1 && !even_starts) << noboolalpha << " " << value << endl;

            return even_starts ? value : -value;
        }

        int64_t leftC = lc(current);
        int64_t rightC = rc(current);
        int64_t m = (l + r) / 2;

        auto rl = modified_get(i, j, leftC, l, m, even_starts);
        auto rr = modified_get(i, j, rightC, m + 1, r, even_starts);
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
    void update(int64_t i, int64_t value) {
        update(i, value, 1, 0, n - 1);
    }
    /**
     * @brief 
     * 
     * @param i 
     * @param j 
     */
    item modified_get(int64_t i, int64_t j) {
        return modified_get(i, j, 1, 0, n - 1, i % 2 == 0);
    }

    void print_st() {
        for (item i: st) {
            cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
    int n;
    cin >> n;

    SegmentTree st(n);
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        st.update(i, ai);
    }


    int m;
    cin >> m;
    while (m--) {
        int op;
        cin >> op;
        if (op == 0) {
            int64_t i, j;
            cin >> i >> j;
            st.update(i - 1, j);
            // st.print_st();
        }
        else {
            assert(op == 1);
            int64_t l, r;
            cin >> l >> r;
            cout << st.modified_get(l - 1, r - 1) << '\n';
        }
    }
    return 0;
}

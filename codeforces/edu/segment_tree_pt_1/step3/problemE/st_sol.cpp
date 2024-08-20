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

    item single(int64_t v) {
        return v;
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

    void add(int64_t i, int64_t to_add, int64_t current, int64_t l, int64_t r) {
        if (outside(l, r, i, i)) return;
        if (l == r) {
            st.at(current) += to_add;
            return;
        }
        int64_t leftC = lc(current);
        int64_t rightC = rc(current);
        int64_t m = (l + r) / 2;

        add(i, to_add, leftC, l, m);
        add(i, to_add, rightC, m + 1, r);
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

    /**
     * @brief Get the index of the kth-one in the binary array
     * Pre-order traversal would be harder, since we cannot deduct the number of 1s from the left subtree
     * to go into the right subtree. Looking ahead into the children's values facilitates this subtraction.
     * @param k 
     * @param current 
     * @param l 
     * @param r 
     * @return int 
     */
    // int get_kth_one(int k, int current, int l, int r) {
    //     if (l == r) {
    //         assert(k == 0);
    //         return l;   // return correct index
    //     }

    //     int leftC = lc(current);
    //     int rightC = rc(current);
    //     int m = (l + r) / 2;

    //     ll lsum = st.at(leftC);
    //     if (k < lsum) { // e.g. k = 2 (want 3rd one). Left? lsum = 2 NO, lsum = 3 YES
    //         return get_kth_one(k, leftC, l, m);
    //     }
    //     return get_kth_one(k - (int) lsum, rightC, m + 1, r);
    // }

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
    void add(int64_t i, int64_t to_add) {
        add(i, to_add, 1, 0, n - 1);
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

    // int get_kth_one(int k) {
    //     return get_kth_one(k, 1, 0, n - 1);
    // }

    /**
     * @brief Inclusive indices. Updates [i, j]
     * add(i, +v)
     * add(j, -v)
     * 
     * @param i 
     * @param j 
     * @param v 
     */
    void range_update(int64_t i, int64_t j, int64_t v) {
        add(i, v);
        add(j + 1, -v);
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    SegmentTree st(n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int64_t l, r, v;
            cin >> l >> r >> v;
            st.range_update(l, r - 1, v);   // inclusive indicies
        }
        else {
            assert(op == 2);
            int64_t i;
            cin >> i;
            cout << st.get(0, i) << '\n';
        }
    }
    return 0;
}

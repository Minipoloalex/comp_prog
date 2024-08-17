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

    item single(int v) {
        return v;
    }
    item combine(item &a, item &b) {
        return a + b;
    }
// private:
public:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts additionally added)
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
    bool outside(int l, int r, int i, int j) {
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
    void update(int i, int value, int current, int l, int r) {
        if (outside(l, r, i, i)) return;
        if (l == r) {
            st.at(current) = single(value);
            return;
        }
        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        update(i, value, leftC, l, m);
        update(i, value, rightC, m + 1, r);
        st.at(current) = combine(st.at(leftC), st.at(rightC));
    }

    item get(int i, int j, int current, int l, int r) {
        if (outside(l, r, i, j)) return NEUTRAL_ELEMENT;
        if (inside(l, r, i, j)) return st.at(current);

        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

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
    int get_kth_one(int k, int current, int l, int r) {
        if (l == r) {
            assert(k == 0);
            return l;   // return correct index
        }

        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        ll lsum = st.at(leftC);
        if (k < lsum) { // e.g. k = 2 (want 3rd one). Left? lsum = 2 NO, lsum = 3 YES
            return get_kth_one(k, leftC, l, m);
        }
        return get_kth_one(k - (int) lsum, rightC, m + 1, r);
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
    void update(int i, int value) {
        update(i, value, 1, 0, n - 1);
    }
    /**
     * @brief 
     * 
     * @param i 
     * @param j 
     */
    item get(int i, int j) {
        return get(i, j, 1, 0, n - 1);
    }

    int get_kth_one(int k) {
        return get_kth_one(k, 1, 0, n - 1);
    }
};

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n;
    cin >> n;
    SegmentTree st(n);
    vector<int> a(n), ans(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        st.update(i, 1);
    }

    for (int i = n - 1; i >= 0; i--) {
        int kth_one_index = st.get_kth_one(a[i]);
        int chosen_nr = n - kth_one_index;
        ans[i] = chosen_nr;
        st.update(kth_one_index, 0);
    }
    for (int r: ans) {
        cout << r << " ";
    }
    cout << '\n';
    return 0;
}

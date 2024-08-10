#include <bits/stdc++.h>
using namespace std;

#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)
// #define p(i) ((i) / 2)

typedef int64_t ll;

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 * 
 */
class SegmentTree {

// private:
public:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts additionally added)
    vector<ll> st;
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
        if (r == l) {
            // cerr << "THERE" << endl;
            st.at(current) = value;
            return;
        }
        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        update(i, value, leftC, l, m);
        update(i, value, rightC, m + 1, r);
        // cerr << "HERE: " << leftC << " " << rightC << endl;
        st.at(current) = st.at(leftC) + st.at(rightC);
    }

    ll get(int i, int j, int current, int l, int r) {
        if (outside(l, r, i, j)) return 0;
        if (inside(l, r, i, j)) return st.at(current);

        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        ll suml = get(i, j, leftC, l, m);
        ll sumr = get(i, j, rightC, m + 1, r);
        return suml + sumr;
    }

public:
    SegmentTree(int _n) {
        size = 1;
        while (size < _n) size <<= 1;
        n = size;
        size <<= 1;
        st.assign(size, 0);
    }
    /**
     * @brief
     * 
     * @param i 1-indexed
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
    ll get(int i, int j) {
        // cerr << "GET CALLED WITH [" << i << ", " << j << "]" << endl;
        return get(i, j, 1, 0, n - 1);
    }
};

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    SegmentTree st(n);
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        // cerr << "Updating: " << i << " " << ai << endl;
        st.update(i, ai);
    }
    // cerr << "Finished updates" << endl;
    // for (ll v: st.st) {
        // cerr << v << " ";
    // }
    // cerr << endl;
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i, v;
            cin >> i >> v;
            // cerr << i << " " << v << endl;
            st.update(i, v);
        }
        else {
            assert(op == 2);
            int l, r;
            cin >> l >> r;
            // cerr << l << " " << r << endl;
            cout << st.get(l, r - 1) << endl;
        }
    }
    return 0;
}

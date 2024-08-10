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
class SegmentTreeMin {
private:
    ll default_value = INT64_MAX;
// private:
public:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts additionally added)
    vector<pair<ll, int>> st;
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
    pair<ll, int> combine(pair<ll, int> &left, pair<ll, int> &right) {
        auto &[minl, cntl] = left;
        auto &[minr, cntr] = right;

        pair<ll, int> ans = make_pair(INT_MAX, 0);
        if (minl < minr) {
            ans.first = minl;
            ans.second = cntl;
        }
        else if (minr < minl) {
            ans.first = minr;
            ans.second = cntr;
        }
        else {  // minl == minr
            ans.first = minl;   // or minr
            ans.second = cntl + cntr;
        }
        return ans;
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
            st.at(current) = make_pair(value, 1);
            return;
        }
        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        update(i, value, leftC, l, m);
        update(i, value, rightC, m + 1, r);
        st.at(current) = combine(st[leftC], st[rightC]);
    }

    pair<ll, int> get(int i, int j, int current, int l, int r) {
        if (outside(l, r, i, j)) return make_pair(default_value, 0);
        if (inside(l, r, i, j)) return st.at(current);

        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        auto rl = get(i, j, leftC, l, m);
        auto rr = get(i, j, rightC, m + 1, r);
        return combine(rl, rr);
    }

public:
    SegmentTreeMin(int _n) {
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
    pair<ll, int> get(int i, int j) {
        return get(i, j, 1, 0, n - 1);
    }
};

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    SegmentTreeMin st(n);
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        st.update(i, ai);
    }

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i, v;
            cin >> i >> v;
            st.update(i, v);
        }
        else {
            assert(op == 2);
            int l, r;
            cin >> l >> r;
            pair<ll, int> ans = st.get(l, r - 1);
            cout << ans.first << " " << ans.second << endl;
        }
    }
    return 0;
}

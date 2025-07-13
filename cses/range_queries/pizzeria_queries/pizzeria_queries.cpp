#include <bits/stdc++.h>
using namespace std;

#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)
 
struct T {
    int left, leftid, right, rightid;
    bool operator==(const T &b) const {
        return left == b.left && leftid == b.leftid && right == b.right && rightid == b.rightid;
    }
    bool operator!=(const T &b) const {
        return !(*this == b);
    }
};
const T iden = {0,-1,0,-1};

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 */
class SegmentTreePizza {
private:
    T default_value = iden;
// private:
public:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts additionally added)
    vector<T> st;
    T f(const T &a, const T &b) {
        if (a == iden) return b;
        if (b == iden) return a;
        T ans;
        int diff_leftid = b.leftid - a.leftid;
        if (a.left < b.left + diff_leftid) {
            ans.left = a.left;
            ans.leftid = a.leftid;
        }
        else {
            ans.left = b.left;
            ans.leftid = b.leftid;
        }

        // ans.left = min(a.left, b.left + diff_leftid);
        // if (a.left == ans.left) ans.leftid = a.leftid;
        // else ans.leftid = b.leftid;

        int diff_rightid = b.rightid - a.rightid;
        if (b.right < a.right + diff_rightid) {
            ans.right = b.right;
            ans.rightid = b.rightid;
        }
        else {
            ans.right = a.right;
            ans.rightid = a.rightid;
        }
        // ans.right = min(b.right, a.right + diff_rightid);
        // if (ans.right == b.right) ans.rightid = b.rightid;
        // else ans.rightid = a.rightid;

        return ans;
    }
    T single(int i, int a) {
        return {a, i, a, i};
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
    SegmentTreePizza(int _n) {
        size = 1;
        while (size < _n) size <<= 1;
        n = size;
        size <<= 1;
 
        // do not need to set this here: could be 0
        // the get function will return the default value
        st.assign(size, default_value);
    }
    SegmentTreePizza(const vector<int> &arr) : SegmentTreePizza(int(arr.size())) {
        for (int i = 0; i < int(arr.size()); i++) {
            update(i, single(i, arr[i]));
        }
    }
 
    // 0-indexed
    void update(int i, T value) {
        update(i, value, 1, 0, n - 1);
    }
    void update(int i, int value) {
        update(i, single(i, value), 1, 0, n - 1);
    }

    // 0-indexed: [i, j]
    T get(int i, int j) {
        return get(i, j, 1, 0, n - 1);
    }
    int query_min_pizza(int i) {
        T left_q = get(0, i - 1);
        T right_q = get(i + 1, n - 1);
        T here = get(i, i); // could handle this inside right_q or left_q
        int ans = here.left;  // same as right
        if (left_q != iden) {
            int diff = i - left_q.rightid;
            ans = min(ans, left_q.right + diff);
        }
        if (right_q != iden) {
            int diff = right_q.leftid - i;
            ans = min(ans, right_q.left + diff);
        }
        return ans;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> p(n);
    for (auto &pi: p) cin >> pi;
    SegmentTreePizza st(p);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, x;
            cin >> k >> x;
            k--;
            st.update(k, x);
        }
        else {
            assert(t == 2);
            int k;
            cin >> k;
            k--;
            cout << st.query_min_pizza(k) << '\n';
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

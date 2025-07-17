#include <bits/stdc++.h>
using namespace std;

// Segment Tree for order statistics
// Needs to process queries offline

#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)
// #define p(i) ((i) / 2)

typedef int64_t T;    // {MAX, first_max_id}
const T iden = 0;

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 */
class SegmentTreeSum {
private:
    T default_value = iden;
// private:
public:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts additionally added)
    vector<T> st;
    T f(const T &a, const T &b) {
        return a + b;
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
    int walk(int current, int l, int r, T sum_value) {
        if (st[current] < sum_value) return -1;
        if (l == r) return l;
        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        if (st[leftC] >= sum_value) {
            return walk(leftC, l, m, sum_value);
        }
        return walk(rightC, m + 1, r, sum_value - st[leftC]);
    }
public:
    SegmentTreeSum(int _n) {
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

    // returns r, s.t.: sum [0, r] = sum_value
    // -1 in case not possible
    int walk(T sum_value) {
        return walk(1, 0, n - 1, sum_value);
    }
};


void solve() {
    int q;
    cin >> q;
    vector<pair<char,int>> qs(q);
    vector<int> values;
    for (auto &[c, x]: qs) {
        cin >> c >> x;
        values.push_back(x);
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    auto get_compressed_idx = [&](int val) {
        return int(lower_bound(values.begin(), values.end(), val) - values.begin());
    };

    SegmentTreeSum st(int(values.size()));
    for (auto &[c, x]: qs) {
        if (c == 'I') {
            int idx = get_compressed_idx(x);
            st.update(idx, 1);
        }
        else if (c == 'D') {
            int idx = get_compressed_idx(x);
            st.update(idx, 0);
        }
        else if (c == 'K') {
            int k = x;
            int idx = st.walk(k);
            if (idx == -1) {
                cout << "invalid" << '\n';
            }
            else cout << values[idx] << '\n';
        }
        else {
            assert(c == 'C');
            int idx = get_compressed_idx(x);
            int smaller_than_x = int(st.get(0, idx - 1));    // strictly smaller than x
            cout << smaller_than_x << '\n';
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

#include <bits/stdc++.h>
using namespace std;


#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)
// #define p(i) ((i) / 2)

typedef int64_t ll;
typedef pair<int,int> T;    // {MAX, first_max_id}
const T iden = {0, -1};

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 */
class SegmentTreeMax {
private:
    T default_value = iden;
// private:
public:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts additionally added)
    vector<T> st;
    T f(const T &a, const T &b) {
        bool fst = a.first > b.first || (a.first == b.first && a.second < b.second);
        return fst ? a : b;
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
    T get_first_larger_than_value(int current, int l, int r, int value) {
        // don't need this if we do an outer check first
        // but it's easier to just keep this here
        if (st[current].first < value) return iden;

        if (l == r) {
            return st[current];
        }
        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;
        T rl = get_first_larger_than_value(leftC, l, m, value);
        if (rl != iden) {
            return rl;
        }
        return get_first_larger_than_value(rightC, m + 1, r, value);
    }
public:
    SegmentTreeMax(int _n) {
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
    T get_first_larger_than_value(int m) {
        return get_first_larger_than_value(1, 0, n - 1, m);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> h(n);
    for (auto &hi: h) cin >> hi;
    SegmentTreeMax st(n);
    for (int i = 0; i < n; i++) {
        st.update(i, {h[i], i});
    }
    while (m--) {
        int ri;
        cin >> ri;
        auto [mx, id] = st.get_first_larger_than_value(ri);
        if (id == -1) {
            cout << "0 ";
        }
        else {
            cout << id + 1 << " ";
            st.update(id, {mx - ri, id});
        }
    }
    cout << '\n';
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

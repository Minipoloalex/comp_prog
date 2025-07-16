#include <bits/stdc++.h>
using namespace std;

#define lc(i) ((i) * 2)
#define rc(i) ((i) * 2 + 1)


typedef array<int64_t,4> T;
const T iden = {INT64_MAX, INT64_MAX, -1, -1};

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
        if (a[0] < b[0]) return a;
        return b;
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
            // This problem requires a small change to the seg-tree
            // Take the min of old vs new
            st[current] = f(st[current], value);
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
    int n, p;
    cin >> n >> p;
    using ev = array<int,4>;
    vector<ev> events;
    vector<int> values;
    vector<int64_t> costs(p, INT64_MAX);
    values.push_back(0);
    auto seg_tree_idx = [&](int val) {
        return int(lower_bound(values.begin(), values.end(), val) - values.begin());
    };
    for (int i = 0; i < p; i++) {
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events.push_back({x1,y1,1,i});
        events.push_back({x2,y2,0,i});
        values.push_back(y1);
        values.push_back(y2);
    }
    sort(events.begin(), events.end());

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    SegmentTree st(int(values.size()));
    st.update(0, {2LL*n, 0, 0, 0});

    for (auto &[x,y,type,i]: events) {
        int idx = seg_tree_idx(y);
        if (type == 1) {
            auto [total_cost, min_cost_to_get_there, srcx, srcy] = st.get(0, idx);
            costs[i] = min_cost_to_get_there + x - srcx + y - srcy;
        }
        else {
            assert(type == 0);
            st.update(idx, {2LL * n - x - y + costs[i], costs[i], x, y});
        }
    }
    auto ans = st.get(0, int(values.size() - 1));
    cout << ans[0] << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

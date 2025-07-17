#include <bits/stdc++.h>
using namespace std;

typedef int64_t T;
const T iden = 0;

/**
 * Represents the type of lazy update being done.
 * NONE = if there's no lazy update to be performed (could be seen as ADD value=0, but this may be more clear)
 */
enum LazyUpdateType { ADD, SET, NONE };

struct LazyUpdate {
    LazyUpdateType type;
    T value;
};

// important that it's 0 (treated like an ADD value=0)
const LazyUpdate update_iden = LazyUpdate{NONE, 0};

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 */
class LazySegmentTree {
private:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the "original" array (counts "elements" artificially added)

    vector<T> st;

    // represents lazy updates (updates that are already complete for the current node, but not for the children)
    vector<LazyUpdate> lz;

    T f(const T &a, const T &b) {
        return a + b;
    }
    /** applies lazy update to st[current], places update at lz[current] */
    void apply_lazy(int current, int l, int r, const LazyUpdate &update) {
        int len = r - l + 1;
        if (update.type == ADD) {
            st[current] += update.value * len;
            if (lz[current].type == ADD || lz[current].type == NONE) {
                lz[current].type = ADD;
                lz[current].value += update.value;
            }
            else {
                lz[current].value += update.value;
            }
        }
        else if (update.type == SET) {
            st[current] = update.value * len;
            lz[current] = update;
        }
    }

    inline int lc(int i) { return i * 2; }
    inline int rc(int i) { return i * 2 + 1; }

    /** All indices are inclusive */
    bool outside(int l, int r, int i, int j) {
        return j < l || r < i;
    }
    /** All indices are inclusive */
    bool inside(int l, int r, int i, int j) {
        return i <= l && r <= j;
    }
    void build(int current, int l, int r, const vector<T> &a) {
        if (l >= int(a.size())) return;
        if (l == r) {
			st[current] = a[l];
		}
        else {
			int m = (l + r) / 2;
            int leftC = lc(current);
            int rightC = rc(current);
            build(leftC, l, m, a);
            build(rightC, m + 1, r, a);
			st[current] = f(st[leftC], st[rightC]);
		}
	}
    /** pushes down lazy updates to children of node current */
    void push_down(int current, int l, int r) {
        int m = (l + r) / 2;
        int leftC = lc(current);
        int rightC = rc(current);
        apply_lazy(leftC, l, m, lz[current]);
        apply_lazy(rightC, m + 1, r, lz[current]);
        lz[current] = update_iden;
    }

    // handles both range_set and range_add
    void range_update(int i, int j, int current, int l, int r, LazyUpdate update) {
        if (outside(l, r, i, j)) return;
        if (inside(l, r, i, j)) {
            apply_lazy(current, l, r, update);
            return;
        }
        // partially inside

        // update children's values with previous lazy updates
        push_down(current, l, r);

        int m = (l + r) / 2;
        int leftC = lc(current);
        int rightC = rc(current);
        range_update(i, j, leftC, l, m, update);
        range_update(i, j, rightC, m + 1, r, update);
        st[current] = f(st[leftC], st[rightC]);
    }
    T range_query(int i, int j, int current, int l, int r) {
        if (outside(l, r, i, j)) return iden;
        if (inside(l, r, i, j)) {
            return st[current];
        }
        push_down(current, l, r);
        int m = (l + r) / 2;
        int leftC = lc(current);
        int rightC = rc(current);
        T rl = range_query(i, j, leftC, l, m);
        T rr = range_query(i, j, rightC, m + 1, r);
        return f(rl, rr);
    }
public:
    LazySegmentTree(int _n) {
        size = 1;
        while (size < _n) size <<= 1;
        n = size;
        size <<= 1;

        st.assign(size, iden);
        lz.assign(size, update_iden);
    }
    LazySegmentTree(const vector<T> &a) : LazySegmentTree(int(a.size())) {
        build(a);
    }
    void build(const vector<T> &a) {
        build(1, 0, n - 1, a);
    }

    /** @return sum of values on [i, j] (0-indexed) */
    T range_query(int i, int j) {
        return range_query(i, j, 1, 0, n - 1);
    }

    /** adds to every value on the range [i, j] (0-indexed) */
    void range_add(int i, int j, T to_add) {
        range_update(i, j, 1, 0, n - 1, LazyUpdate{ADD, to_add});
    }
    /** sets every value on the range [i, j] (0-indexed) */
    void range_set(int i, int j, T to_set) {
        range_update(i, j, 1, 0, n - 1, LazyUpdate{SET, to_set});
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int64_t> t(n);
    for (auto &ti: t) cin >> ti;
    LazySegmentTree st(t);

    while (q--) {
        int type;
        cin >> type;
        int a, b;
        cin >> a >> b;
        a--;b--;
        if (type == 1) {
            int to_add;
            cin >> to_add;
            st.range_add(a, b, to_add);
        }
        else if (type == 2) {
            int to_set;
            cin >> to_set;
            st.range_set(a, b, to_set);
        }
        else {
            assert(type == 3);
            cout << st.range_query(a, b) << '\n';
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

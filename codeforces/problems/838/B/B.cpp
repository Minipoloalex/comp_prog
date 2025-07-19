#include <bits/stdc++.h>
using namespace std;

typedef int64_t T;
const T iden = INT64_MAX;

/**
 * Represents the type of lazy update being done.
 * NONE = if there's no lazy update to be performed (could be seen as ADD value=0, but this may be more clear)
 */
enum LazyUpdateType { ADD, NONE };

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
        return min(a, b);
    }
    /** applies lazy update to st[current], places update at lz[current] */
    void apply_lazy(int current, int l, int r, const LazyUpdate &update) {
        if (update.type == ADD) {
            st[current] += update.value;
            lz[current].type = ADD;
            lz[current].value += update.value;
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
    void range_update(int i, int j, int current, int l, int r, const LazyUpdate &update) {
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
};

// Usage:
// FenwickTree ft(n);
// 1-indexed on n:
// e.g. Sum[0:n-1] = ft.rsq(1, n);

#define LSOne(S) ((S) & -(S)) // the key operation

typedef long long ll; // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

// 1-indexed
class FenwickTree
{ // index 0 is not used
private:
    vll ft; // internal FT is an array
public:
    FenwickTree(int m) { ft.assign(m + 1, 0); } // create an empty FT

    void build(const vll &f)
    {
        int m = (int)f.size() - 1; // note f[0] is always 0
        ft.assign(m + 1, 0);
        for (int i = 1; i <= m; ++i)
        {                                  // O(m)
            ft[i] += f[i];                 // add this value
            if (i + LSOne(i) <= m)         // i has parent
                ft[i + LSOne(i)] += ft[i]; // add to that parent
        }
    }

    FenwickTree(const vll &f) { build(f); } // create FT based on f

    FenwickTree(int m, const vi &s)
    { // create FT based on s
        vll f(m + 1, 0);
        for (int i = 0; i < (int)s.size(); ++i) // do the conversion first
            ++f[s[i]];                          // in O(n)
        build(f);                               // in O(m)
    }

    ll rsq(int j)
    { // returns RSQ(1, j)
        ll sum = 0;
        for (; j; j -= LSOne(j))
            sum += ft[j];
        return sum;
    }

    ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); } // inc/exclusion

    // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
    void update(int i, ll v)
    {
        for (; i < (int)ft.size(); i += LSOne(i))
            ft[i] += v;
    }

    int select(ll k)
    { // O(log m)
        int p = 1;
        while (p * 2 < (int)ft.size())
            p *= 2;
        int i = 0;
        while (p)
        {
            if (k > ft[i + p])
            {
                k -= ft[i + p];
                i += p;
            }
            p /= 2;
        }
        return i + 1;
    }
};

// 1-indexed
class RUPQ
{ // RUPQ variant
private:
    FenwickTree ft; // internally use PURQ FT
public:
    RUPQ(int m) : ft(FenwickTree(m)) {}
    /**
     * @brief Inclusive update: [ui, uj]
     * 
     * @param ui 
     * @param uj 
     * @param v 
     */
    void range_update(int ui, int uj, ll v)
    {
        ft.update(ui, v);                       // [ui, ui+1, .., m] +v
        ft.update(uj + 1, -v);                  // [uj+1, uj+2, .., m] -v
    }                                           // [ui, ui+1, .., uj] +v
    ll point_query(int i) { return ft.rsq(i); } // rsq(i) is sufficient
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<pair<int,int64_t>>> g(n + 1);
    vector<pair<int,int64_t>> edges = {{-1,-1}};
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        int64_t w;
        cin >> a >> b >> w;
        g[a].emplace_back(b, w);
        edges.emplace_back(b, w);
    }
    vector<int64_t> ws(n + 1, 0);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        int64_t w;
        cin >> a >> b >> w;
        assert(b == 1);
        ws[a] = w;
        edges.emplace_back(a, w);
    }

    int timer = 1;
    vector<int> st(n + 1), end(n + 1);
    vector<int64_t> cost(n + 1);
    vector<int64_t> upcost(n + 1, 0);
    function<void(int,int64_t)> dfs = [&](int u, int64_t cur) {
        cost[timer] = cur;
        upcost[timer] = cur + ws[u];
        st[u] = timer++;
        for (auto &[v, w]: g[u]) {
            dfs(v, cur + w);
        }
        end[u] = timer;
    };
    dfs(1, 0);

    RUPQ ft(n);
    for (int i = 1; i <= n; i++) {
        ft.range_update(i, i, cost[i]);
    }
    LazySegmentTree segtree(upcost);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int i;
            int64_t w;
            cin >> i >> w;
            if (i <= n - 1) {   // [1, n - 1]
                auto &[dst, prevw] = edges[i];
                int64_t to_add = w - prevw;

                int stidx = st[dst];
                int endidx = end[dst] - 1;  // end is exclusive, ft is inclusive
                ft.range_update(stidx, endidx, to_add);
                segtree.range_add(stidx, endidx, to_add);
                edges[i].second = w;
            }
            else {  // [n, 2*n - 2]
                auto &[src, _] = edges[i];
                int64_t diff = w - ws[src];
                ws[src] = w;
                segtree.range_add(st[src], st[src], diff);
                edges[i].second = w;    // unnecessary, but for consistency
            }
        }
        else {
            assert(type == 2);
            int u, v;
            cin >> u >> v;
            int64_t ans = 0;

            // if v is on u's subtree
            if (st[u] <= st[v] && end[v] <= end[u]) {
                // can go from u directly to v (without going "backwards")
                // accounts for u == v
            }
            else {
                ans = segtree.range_query(st[u], end[u] - 1) - ft.point_query(st[u]);
                // needs to go through root first, then can move to v
                u = 0;
            }

            int64_t from_root_to_u = ft.point_query(st[u]);
            int64_t from_root_to_v = ft.point_query(st[v]);
            ans += (from_root_to_v - from_root_to_u);
            cout << ans << '\n';
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

#include <bits/stdc++.h>
using namespace std;

#define lc(i) (2 * (i))
#define rc(i) (2 * (i) + 1)

typedef int64_t ll;

/**
 * @brief By convention, l and r mean the interval of the current node, while i and j mean the 
 * interval that we are working on (e.g., getting its value, or updating it).
 */
class SegmentTree {

private:
    int size;   // 2 * n (size of the segment tree array)
    int n;      // size of the original array
    vector<ll> st;
    ll mod;      // the mod used for this problem
    ll DEFAULT = 1;
public:
    int walk_index = -1;
private:

    bool outside(int l, int r, int i, int j) {
        return j < l || r < i;
    }

    bool inside(int l, int r, int i, int j) {
        return i <= l && r <= j;
    }
    ll combine(ll lr, ll rr) {
        return (lr * rr) % mod;
    }

    void update(int i, int value, int current, int l, int r) {
        if (outside(l, r, i, i)) return;
        if (r == l) {
            st[current] = value;
            return;
        }
        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        update(i, value, leftC, l, m);
        update(i, value, rightC, m + 1, r);
        st[current] = combine(st[leftC], st[rightC]);
    }

    ll get(int i, int j, int current, int l, int r) {
        if (outside(l, r, i, j)) return DEFAULT;
        if (inside(l, r, i, j)) return st[current];

        int leftC = lc(current);
        int rightC = rc(current);
        int m = (l + r) / 2;

        ll rl = get(i, j, leftC, l, m);
        ll rr = get(i, j, rightC, m + 1, r);
        return combine(rl, rr);
    }

    ll walk(int l, int r, int current, ll cur_value) {
        if (l == r) {
            // instead of saving the index like this (and returning values, which is a bad way of doing this)
            // we could: first test if it is possible to achieve (return -1 if not)
            // then, we can just return the index instead of the value, since we already know it's possible
            // also, we could just test here for -1 since we have access to cur_value
            walk_index = l;
            return st[current];
        }
        int m = (l + r) / 2;
        int leftC = lc(current);
        int rightC = rc(current);
        ll rl = st[leftC];
        if (cur_value * rl % mod == 0) {  // 0 mod k
            // go left
            return walk(l, m, leftC, cur_value);
        }
        else {  // go right, and include (all) values from the left
            ll ncur_value = cur_value * rl % mod;
            ll rr = walk(m + 1, r, rightC, ncur_value);
            return combine(rl, rr);
        }
    }

public:
    SegmentTree(int _n, int k) {
        size = 1;
        while (size < _n) size <<= 1;
        n = size;
        size <<= 1;
        st.assign(size, DEFAULT); // Default value for multiplication is 1
        mod = k;
    }

    void update(int i, int value) {
        value %= int(mod);
        update(i, value, 1, 0, n - 1);
    }

    ll get(int i, int j) {
        return get(i, j, 1, 0, n - 1);
    }
    ll walk() {
        // will return the first index that corresponds to the prefix where the multiplication is 0 mod k
        return walk(0, n - 1, 1, 1);
    }
};

void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int pi;
        cin >> pi;
        pi--;
        g[pi].push_back(i);
    }
    vector<vector<pair<int,int>>> qs(n);
    for (int i = 1; i <= q; i++) {
        int ui, xi;
        cin >> ui >> xi;
        ui--;
        qs[ui].emplace_back(i, xi);
    }
    SegmentTree st(q + 1, k);
    vector<int> ans(n);
    function<void(int)> dfs = [&](int u) {
        st.update(0, a[u]);
        for (auto &[idx, x]: qs[u]) {
            st.update(idx, x);  // fine since all indices are unique
        }
        ll res = st.walk();
        int year = st.walk_index;
        if (res != 0) year = -1;   // not possible
        st.update(0, 1);

        ans[u] = int(year);
        for (int v: g[u]) {
            dfs(v);
        }
        for (auto &[idx, x]: qs[u]) {
            st.update(idx, 1);
        }
    };
    dfs(0);
    for (int v: ans) cout << v << " ";
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

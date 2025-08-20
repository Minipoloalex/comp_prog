#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;

// point update, range query; 0-indexed
// supports non-commutative functions
template <typename T>
struct seg_tree {
    // Neutral element: inf in min seg_tree, 0 in sum seg_tree, ...
    const T iden = {INT_MAX, 0};

    int n;
    vector<T> t;

    // Round n to the next power of 2
    seg_tree(int sz) : n(1 << int(ceil(log2(sz)))), t(2 * n, iden) {}

    // Constructor from array
    seg_tree(const vector<T>& v) :
        n(1 << int(ceil(log2(v.size())))),
        t(2 * n, iden) {
        for (int i = 0; i < int(v.size()); i++) {
            update(i, v[i]);
        }
    }

    T f(const T& l, const T& r) {
        auto &[ml, cl] = l;
        auto &[mr, cr] = r;
        if (ml == mr) {
            return {ml, (cl + cr) % MOD};
        }
        else if (ml < mr) {
            return l;
        }
        else {
            return r;
        }
    }

    // Point update in position p, 0-indexed
    void update(int p, T val) {
        p += n;
        t[p] = f(t[p], val);
        for (p >>= 1; p > 0; p >>= 1)
            t[p] = f(t[p << 1], t[p << 1 | 1]);
    }

    // Range [l, r); Keeps left and right results separate for non-commutative f
    T query(int l, int r) {
        T l_res = iden, r_res = iden;

        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            // if l is odd, then l is a right child and this interval is contained in the result
            if (l & 1) l_res = f(l_res, t[l++]);

            // if r is odd, then r - 1 is a left child contained in the result
            if (r & 1) r_res = f(t[--r], r_res);
        }

        return f(l_res, r_res);
    }

    // Returns the first index i where arr[i] >= val, in max seg tree, or -1 if it does not exist
    // Can be adapted to similar 'walk' queries in min and sum seg trees
    int walk(T val) {
        int p = 1;
        if (t[p] < val) return -1; // no element >= val
        while (p < n) {
            if (t[p << 1] >= val) p = p << 1;
            else p = p << 1 | 1;
        }
        return p - n;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> d(n + 1);
    vector<int> vals; vals.reserve(2*n);
    int mxIN = 0;
    for (int i = 1; i <= n; i++) {
        int out, in;
        cin >> out >> in;
        d[i] = {in, out};
        mxIN = max(mxIN, in);
        vals.push_back(d[i].first);
        vals.push_back(d[i].second);
    }
    sort(d.begin(), d.end());

    vals.push_back(0);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto get_compressed_idx = [&vals](int val) {
        return int(lower_bound(vals.begin(), vals.end(), val) - vals.begin());
    };

    using T = pair<int,int64_t>;
    seg_tree<T> st(int(vals.size()));
    st.update(0, {0,1});

    int mnANS = INT_MAX;
    vector<T> dp(n + 1);
    for (int i = 1; i <= n; i++) {
        auto &[in, out] = d[i];
        int inidx = get_compressed_idx(in);
        int outidx = get_compressed_idx(out);
        auto [mn, cnt] = st.query(0, inidx + 1);
        dp[i] = {mn + in, cnt}; // dp[i] = min(dp[j] + INi - OUTj)

        st.update(outidx, {dp[i].first - out, dp[i].second});

        if (out > mxIN) {
            mnANS = min(mnANS, dp[i].first);
        }
    }

    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        auto &[in, out] = d[i];
        auto &[cost, cnt] = dp[i];
        if (cost == mnANS && out > mxIN) {
            ans += cnt;
            ans %= MOD;
        }
    }
    cout << ans << '\n';
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

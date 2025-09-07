#include <bits/stdc++.h>
using namespace std;

// These are both implicit monotonic stack-based approaches (assume a valid comparator cmp: transitivity)
/**
 * For each position, gives the 0-based index of the closest element on the left of it for which cmp is true
 * Gives -1 if there's none
 * Formally, for each index i, gives the first index on the left j < i, s.t. cmp(a[j], a[i]) is true
 * Usage:
 *  auto pg = closest_left(a, greater<int>());   // for previous (strictly) greater
 */
template<typename T, typename Pred>
vector<int> closest_left(const vector<T> &a, Pred cmp) {
    int n = int(a.size()); vector<int> closest(n); iota(closest.begin(), closest.end(), -1);
    for (int i = 0; i < n; i++) {
        auto &j = closest[i];
        while(j >= 0 && !cmp(a[j], a[i])) j = closest[j];
    }
    return closest;
}
// point update, range query; 0-indexed
// supports non-commutative functions
template <typename T>
struct seg_tree {
    // Neutral element: inf in min seg_tree, 0 in sum seg_tree, ...
    const T iden = numeric_limits<T>::min();

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
        return max(l, r);
    }

    // Point update in position p, 0-indexed
    void update(int p, T val) {
        t[p += n] = val;
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
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    vector<int> prv = closest_left(a, greater_equal<int>());
    seg_tree st(a);
    vector<int> prv2(n);
    auto possible = [&](int l, int i) {
        return st.query(l, i) >= b[i];  // should have used a sparse table instead (for O(1) queries)
    };
    for (int i = 0; i < n; i++) {
        int lo = 0, hi = i - 1;
        while (lo < hi) {
            int m = lo + (hi - lo + 1) / 2;
            if (possible(m, i)) {
                lo = m;
            }
            else {
                hi = m - 1;
            }
        }
        if (possible(lo, i)) prv2[i] = lo;
        else prv2[i] = -1;
    }
    int64_t to_remove = 0;
    int64_t all = 0;
    for (int sz = 1; sz <= n; sz++) {
        all += 1LL * (n - sz + 1) * sz;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) continue;
        int j = min(prv[i], prv2[i]);
        to_remove += 1LL * (i - j) * (n - i);    // cases where it must appear as x[i] instead of y[i]
    }
    int64_t ans = all - to_remove;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

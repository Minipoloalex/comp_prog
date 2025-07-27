#include <bits/stdc++.h>
using namespace std;

// supports point update, range query
template <typename T>
struct seg_tree {
    int n;
    vector<T> t;

    // neutral element: inf in min seg_tree, 0 in sum seg_tree, ...
    static constexpr T iden = numeric_limits<T>::max();

    seg_tree(int sz) : n(sz), t(2 * sz, iden) {}

    seg_tree(const vector<T>& arr) : n(int(arr.size())), t(2 * n) {
        for (int i = 0; i < n; i++)
            update(i, arr[i]);
    }

    T f(const T& a, const T& b) {
        return min(a, b);
    }

    void update(int p, T val) { // point update in position p
        t[p += n] = val;
        for (p >>= 1; p > 0; p >>= 1)
            t[p] = f(t[p << 1], t[p << 1 ^ 1]);
    }

    T query(int l, int r) { // range [l, r)
        T res = iden;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = f(res, t[l++]);
            if (r & 1) res = f(res, t[--r]);
        }
        return res;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    auto possible = [&](int x) -> tuple<bool,int,int> {
        vector<int> pref(n + 1);
        for (int i = 1; i <= n; i++) {
            int v = a[i] >= x ? 1 : -1;
            pref[i] = pref[i - 1] + v;
        }
        seg_tree<int> st(2*n + 10);
        map<int,int> mp;
        mp[pref[0]] = 0;
        st.update(pref[0] + n, 0);
        for (int i = 1; i <= n; i++) {
            int mn = st.query(0, pref[i] + n + 1);
            if (mn != INT_MAX) {
                if (i - mn >= k) {
                    return {true, mn + 1, i};
                }
            }
            if (!mp.contains(pref[i])) {
                mp[pref[i]] = i;
                st.update(pref[i] + n, i);
            }
        }
        return {false, -1, -1};
    };
    int lo = 1, hi = n;
    while (lo < hi) {
        int med = lo + (hi - lo + 1) / 2;
        auto [can, l, r] = possible(med);
        if (can) {
            lo = med;
        }
        else {
            hi = med - 1;
        }
    }
    auto [can, l, r] = possible(lo);
    assert(can);
    cout << lo << " " << l << " " << r << '\n';
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

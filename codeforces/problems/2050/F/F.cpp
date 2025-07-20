#include <bits/stdc++.h>
using namespace std;

// supports point update, range query
template <typename T>
struct seg_tree {
    int n;
    vector<T> t;

    // neutral element: inf in min seg_tree, 0 in sum seg_tree, ...
    const T iden = 0;

    seg_tree(int sz) : n(sz), t(2 * sz, iden) {}

    seg_tree(const vector<T>& arr) : n(int(arr.size())), t(2 * n) {
        for (int i = 0; i < n; i++)
            update(i, arr[i]);
    }

    T f(const T& a, const T& b) {
        return gcd(a, b);
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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> diff(n-1);
    for (int i = 1; i < n; i++) {
        diff[i - 1] = a[i] - a[i - 1];
    }
    seg_tree<int> st(diff);
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;r--;
        int g = st.query(l, r);
        cout << g << " ";
    }
    cout << '\n';
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

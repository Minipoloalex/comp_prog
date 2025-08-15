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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    map<int,int> pos;
    vector<array<int,3>> intervals;
    for (int i = 0; i < n; i++) {
        if (pos.contains(a[i])) {
            int l = pos[a[i]];
            int r = i;
            int sz = r - l;
            intervals.push_back({l, r, sz});
        }
        pos[a[i]] = i;
    }
    // vector<array<int,3>> qs(m);
    // bucket queries by their right endpoint instead of sorting them
    vector<vector<pair<int,int>>> qs(n);
    for (int i = 0; i < m; i++) {
        int li, ri;
        cin >> li >> ri;
        li--;
        ri--;
        qs[ri].emplace_back(li, i);
        // qs[i] = {ri, li, i};
    }
    seg_tree<int> st(n);
    vector<int> ans(m);
    int intervalidx = 0;
    for (int qr = 0; qr < n; qr++) {
        while (intervalidx < int(intervals.size()) && intervals[intervalidx][1] <= qr) {
            st.update(intervals[intervalidx][0], intervals[intervalidx][2]);
            intervalidx++;
        }
        for (auto &[ql, origidx]: qs[qr]) {
            int mn = st.query(ql, qr + 1);
            if (mn == INT_MAX) mn = -1;
            ans[origidx] = mn;
        }
    }
    // sorting the queries like this would TLE
    // sort(qs.begin(), qs.end());
    // for (int i = 0; i < m; i++) {
    //     auto &[qr, ql, origidx] = qs[i];
    //     while (intervalidx < int(intervals.size()) && intervals[intervalidx][1] <= qr) {
    //         st.update(intervals[intervalidx][0], intervals[intervalidx][2]);
    //         intervalidx++;
    //     }
    //     int mn = st.query(ql, qr + 1);
    //     if (mn == INT_MAX) mn = -1;
    //     ans[origidx] = mn;
    // }
    for (int v: ans) cout << v << '\n';
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

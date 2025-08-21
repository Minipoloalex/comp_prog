#include <bits/stdc++.h>
using namespace std;

// point update, range query; 0-indexed
// supports non-commutative functions
template <typename T, class F>
struct seg_tree {
    // Neutral element: inf in min seg_tree, 0 in sum seg_tree, ...
    F f;
    T iden;

    int n;
    vector<T> t;

    // Round n to the next power of 2
    seg_tree(int sz) : n(1 << int(ceil(log2(sz)))), t(2 * n, iden) {}

    // Constructor from array
    seg_tree(const vector<T>& v, F _f, T _iden) :
        f(_f), iden(_iden),
        n(1 << int(ceil(log2(v.size())))),
        t(2 * n, iden) {
        for (int i = 0; i < int(v.size()); i++) {
            update(i, v[i]);
        }
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

using ii = pair<int,int>;

void solve() {
    auto fmax = [](ii a, ii b) {
        auto &[idxa, aval] = a;
        auto &[idxb, bval] = b;
        if (aval > bval) {
            return a;
        }
        else {
            return b;
        }
    };
    auto fmin = [](ii a, ii b) {
        auto &[idxa, aval] = a;
        auto &[idxb, bval] = b;
        if (aval < bval) {
            return a;
        }
        else {
            return b;
        }
    };

    int n, a, b;
    cin >> n >> a >> b;
    a--;b--;
    vector<ii> pleft(n), pright(n);
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        pright[i] = {i, i - p[i]};
        pleft[i] = {i, i + p[i]};
    }
    ii DEF_RIGHT = {-1, INT_MAX};
    ii DEF_LEFT = {-1, INT_MIN};
    seg_tree stleft(pleft, fmax, DEF_LEFT);
    seg_tree stright(pright, fmin, DEF_RIGHT);

    auto destroy = [&](int idx) {
        stleft.update(idx, DEF_LEFT);
        stright.update(idx, DEF_RIGHT);
    };

    auto edges = [&](int x) {
        vector<int> ans;
        // we can include x in the queries because it's been invalidated already

        while (true) {  // check the right
            auto [y, yval] = stright.query(x, min(n, x + p[x] + 1));    // +1 on right, because [l, r)
            if (x >= yval) {
                ans.push_back(y);
                destroy(y);
            }
            else {
                break;
            }
        }
        while (true) {  // check the left
            auto [y, yval] = stleft.query(max(0, x - p[x]), x + 1); // [..., x]
            if (x <= yval) {
                ans.push_back(y);
                destroy(y);
            }
            else {
                break;
            }
        }
        return ans;
    };
    queue<int> q;
    vector<int> dist(n, 0);
    q.push(a);
    destroy(a);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: edges(u)) { // already marked not to visit again
            q.push(v);
            dist[v] = dist[u] + 1;
        }
    }
    cout << dist[b] << '\n';
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

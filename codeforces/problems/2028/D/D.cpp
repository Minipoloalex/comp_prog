#include <bits/stdc++.h>
using namespace std;

string chars = "qkj";


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
    vector<vector<int>> a(3,vector<int>(n));
    vector<vector<int>> pos(3,vector<int>(n));
    vector<seg_tree<int>> trees;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            int val; cin >> val;
            val--;
            a[i][val] = j;
            pos[i][j] = val;
        }
        trees.emplace_back(a[i]);
    }
    vector<pair<int,int>> par(n,{-1,-1});
    auto visit = [&](int x, int p, int i) {
        par[x] = {p,i};
        for (int j = 0; j < 3; j++) {
            trees[j].update(pos[j][x], INT_MIN);
        }
    };
    queue<int> q;
    q.push(0);
    visit(0,-1,-1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < 3; i++) {
            while (true) {
                int ind = trees[i].walk(u);
                if (ind == -1 || ind >= pos[i][u]) {
                    break;
                }
                int v = a[i][ind];
                q.push(v);
                visit(v, u, i);
            }
        }
    }
    int cur = n-1;
    vector<pair<int,char>> ans;
    bool yes = true;
    while (cur > 0) {
        auto &[prv, i] = par[cur];
        if (prv == -1) {
            yes = false;
            break;
        }
        char c = chars[i];
        ans.emplace_back(cur, c);
        cur = prv;
    }
    reverse(ans.begin(), ans.end());
    if (yes) {
        cout << "YES\n";
        cout << ans.size() << '\n';
        for (auto &[nr, ch]: ans) {
            cout << ch << " " << nr+1 << '\n';
        }
    }
    else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

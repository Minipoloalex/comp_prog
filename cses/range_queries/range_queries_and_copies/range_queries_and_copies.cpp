#include <bits/stdc++.h>
using namespace std;

struct Vertex {
    int64_t sum = 0;
    Vertex *left = nullptr, *right = nullptr;
    Vertex(int64_t v) : sum(v) {}
    Vertex(Vertex *l, Vertex *r) : left(l), right(r) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};
Vertex *build(int l, int r, const vector<int> &a) {
    if (l == r) {
        return new Vertex(a[l]);
    }
    int m = (l + r) >> 1;
    Vertex *left = build(l, m, a);
    Vertex *right = build(m + 1, r, a);
    return new Vertex(left, right);
}
Vertex *update(Vertex *root, int l, int r, int pos, int new_val) {
    if (l == r) {
        return new Vertex(new_val);
    }
    int m = (l + r) >> 1;
    if (pos <= m) {
        return new Vertex(update(root->left, l, m, pos, new_val), root->right);
    }
    return new Vertex(root->left, update(root->right, m + 1, r, pos, new_val));
}
int64_t query(Vertex *root, int l, int r, int ql, int qr) {
    if (r < ql || l > qr) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return root->sum;
    }
    int m = (l + r) >> 1;
    return query(root->left, l, m, ql, qr) + query(root->right, m + 1, r, ql, qr);
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> t(n);
    for (auto &ti: t) cin >> ti;
    vector<Vertex*> roots = {build(0, n - 1, t)};
    while (q--) {
        int type, k;
        cin >> type >> k;
        k--;
        if (type == 1) {
            int a, x;
            cin >> a >> x;
            a--;
            roots[k] = update(roots[k], 0, n - 1, a, x);
        }
        else if (type == 2) {
            int a, b;
            cin >> a >> b;
            a--;b--;
            int64_t ans = query(roots[k], 0, n - 1, a, b);
            cout << ans << '\n';
        }
        else {
            assert(type == 3);
            roots.push_back(roots[k]);
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

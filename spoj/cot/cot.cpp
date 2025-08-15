#include <bits/stdc++.h>
using namespace std;

class Tree {
    private:
        int n;
        vector<int> par;
        vector<vector<int>> pow2ends;
        vector<int> depth;
        const int log2dist;
    public:
        Tree(const vector<int>& parents)
                : par(parents.size()),
                  log2dist(int(ceil(log2(parents.size() + 1)))) {
            n = int(parents.size());
            par = parents;

            pow2ends = vector<vector<int>>(n, vector<int>(log2dist + 1));
            for (int i = 0; i < n; i++) {
                pow2ends[i][0] = par[i];
            }
            for (int p = 1; p <= log2dist; p++) {
                for (int i = 0; i < n; i++) {
                    int halfway = pow2ends[i][p - 1];
                    if (halfway == -1) {
                        pow2ends[i][p] = -1;
                    } else {
                        pow2ends[i][p] = pow2ends[halfway][p - 1];
                    }
                }
            }
            vector<vector<int>> children(n);
            for (int i = 1; i < n; i++) {
                children[par[i]].push_back(i);
            }

            depth = vector<int>(n);
            vector<int> frontier = {0};
            while (!frontier.empty()) {
                int src = frontier.back();
                frontier.pop_back();
                for (int dst : children[src]) {
                    depth[dst] = depth[src] + 1;
                    frontier.push_back(dst);
                }
            }
        }
        int kth_parent(int src, int k) {
            if (k > n) {
                return -1;
            }
            int at = src;
            for (int pow = 0; pow <= log2dist; pow++) {
                if ((k & (1 << pow)) != 0) {
                    at = pow2ends[at][pow];
                    if (at == -1) {
                        break;
                    }
                }
            }
            return at;
        }
        int lca(int n1, int n2) {
            if (depth[n1] < depth[n2]) {
                return lca(n2, n1);
            }
            n1 = kth_parent(n1, depth[n1] - depth[n2]);
            if (n1 == n2) {
                return n1;
            }
            for (int i = log2dist; i >= 0; i--) {
                if (pow2ends[n1][i] != pow2ends[n2][i]) {
                    n1 = pow2ends[n1][i];
                    n2 = pow2ends[n2][i];
                }
            }
            return pow2ends[n1][0];
        }
};

template<class T, class F>
struct persistent_segtree {
    struct Node { T val; int l, r; };
    int n;
    vector<Node> st;
    F f;
    T iden;

    persistent_segtree(int _n, F _f, T _iden, int reserve_nodes = 0)
        : n(_n), f(_f), iden(_iden) {
        st.reserve(max(1, reserve_nodes));
        st.push_back(Node{iden, 0, 0});
    }
    int new_node(const Node &x){ st.push_back(x); return int(st.size())-1; }
    int make_leaf(const T &v){ return new_node(Node{v, 0, 0}); }

    int build(int tl, int tr, const vector<T> &a){
        if (tl == tr) return make_leaf(a[tl]);
        int tm = (tl + tr) >> 1;
        int L = build(tl, tm, a), R = build(tm+1, tr, a);
        return new_node(Node{ f(st[L].val, st[R].val), L, R });
    }
    int update(int node, int tl, int tr, int pos, const T &val) {
        if (tl == tr) return make_leaf(val);
        int tm = (tl + tr) >> 1;
        int L = st[node].l, R = st[node].r;
        if (pos <= tm) L = update(L, tl, tm, pos, val);
        else           R = update(R, tm+1, tr, pos, val);
        return new_node(Node{ f(st[L].val, st[R].val), L, R });
    }
    T query(int node, int tl, int tr, int ql, int qr) const {
        if (qr < tl || tr < ql) return iden;
        if (ql <= tl && tr <= qr) return st[node].val;
        int tm = (tl + tr) >> 1;
        return f(query(st[node].l, tl, tm, ql, qr),
                 query(st[node].r, tm+1, tr, ql, qr));
    }
    int build(const vector<T> &a){ return build(0, n-1, a); }
    int update(int root, int pos, const T &val){ return update(root, 0, n-1, pos, val); }
    T query(int root, int ql, int qr) const {
        return query(root, 0, n - 1, ql, qr);
    }

    template<class Pred>
    int find_first(int nodeu, int nodev, int nodelca, int nodepar, int tl, int tr,
        const T &accU, const T &accV, const T &accLCA, const T &accPar, const Pred &pred) {
        T   allU = f(accU,   st[nodeu  ].val);
        T   allV = f(accV,   st[nodev  ].val);
        T allLCA = f(accLCA, st[nodelca].val);
        T allPar = f(accPar, st[nodepar].val);
        if (!pred(allU, allV, allLCA, allPar)) return -1;
        if (tl == tr) return tl;

        int tm = (tl + tr) >> 1;
        int   uL = st[nodeu  ].l,   uR = st[nodeu  ].r;
        int   vL = st[nodev  ].l,   vR = st[nodev  ].r;
        int lcaL = st[nodelca].l, lcaR = st[nodelca].r;
        int parL = st[nodepar].l, parR = st[nodepar].r;
        T   leftU = f(accU,   st[uL  ].val);
        T   leftV = f(accV,   st[vL  ].val);
        T leftLCA = f(accLCA, st[lcaL].val);
        T leftPar = f(accPar, st[parL].val);
        if (pred(leftU, leftV, leftLCA, leftPar)) {
            return find_first(uL, vL, lcaL, parL, tl, tm, accU, accV, accLCA, accPar, pred);
        }
        return find_first(uR, vR, lcaR, parR, tm + 1, tr, leftU, leftV, leftLCA, leftPar, pred);
    }
    template<class Pred>
    int find_first(int uroot, int vroot, int lcaroot, int lcaparentroot, const Pred &pred) {
        return find_first(uroot, vroot, lcaroot, lcaparentroot, 0, n - 1, iden, iden, iden, iden, pred);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> ws(n);
    for (auto &wi: ws) cin >> wi;

    vector<int> sortedws = ws;
    sort(sortedws.begin(), sortedws.end());
    sortedws.erase(unique(sortedws.begin(), sortedws.end()), sortedws.end());
    auto get_compressed_idx = [&](int v) {
        return int(lower_bound(sortedws.begin(), sortedws.end(), v) - sortedws.begin());
    };

    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto fsum = [](int a, int b) { return a + b; };
    persistent_segtree<int,decltype(fsum)> st(n, fsum, 0, 22*n);

    vector<int> id(n);
    vector<int> par(n);

    int timer = 1;
    vector<int> roots(n + 1);
    roots[0] = 0;

    // to keep track of values since the seg tree sets values (cannot just add +1)
    vector<int> compressed_sum(n);

    function<void(int,int)> dfs = [&](int u, int p) {
        par[u] = p;
        id[u] = timer++;
        int prev_root;
        if (p == -1) prev_root = 0;
        else {
            prev_root = roots[id[p]];
        }

        int compressed_idx = get_compressed_idx(ws[u]);
        compressed_sum[compressed_idx]++;
        roots[id[u]] = st.update(prev_root, compressed_idx, compressed_sum[compressed_idx]);

        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        compressed_sum[compressed_idx]--;
    };
    dfs(0, -1);
    Tree t(par);
    while (m--) {
        int u, v, k;
        cin >> u >> v >> k;
        u--;v--;
        int lca = t.lca(u, v);
        int lcaroot = roots[id[lca]];
        int uroot = roots[id[u]];
        int vroot = roots[id[v]];
        int lcaparentroot = par[lca] == -1 ? 0 : roots[id[par[lca]]];
        int idx = st.find_first(uroot, vroot, lcaroot, lcaparentroot,
            [k](int ucnt, int vcnt, int lcacnt, int lcaparentcnt) {
            return ucnt + vcnt - lcacnt - lcaparentcnt >= k;
        });
        cout << sortedws[idx] << '\n';
    }
}

int main() {
    // to submit, minify the code
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

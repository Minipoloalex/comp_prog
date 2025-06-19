#include <bits/stdc++.h>
using namespace std;
// Usage:
// FenwickTree ft(n);
// 1-indexed on n:
// e.g. Sum[0:n-1] = ft.rsq(1, n);

#define LSOne(S) ((S) & -(S)) // the key operation

typedef long long ll; // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

// 1-indexed
class FenwickTree
{ // index 0 is not used
private:
    vll ft; // internal FT is an array
public:
    FenwickTree(int m) { ft.assign(m + 1, 0); } // create an empty FT

    void build(const vll &f)
    {
        int m = (int)f.size() - 1; // note f[0] is always 0
        ft.assign(m + 1, 0);
        for (int i = 1; i <= m; ++i)
        {                                  // O(m)
            ft[i] += f[i];                 // add this value
            if (i + LSOne(i) <= m)         // i has parent
                ft[i + LSOne(i)] += ft[i]; // add to that parent
        }
    }

    FenwickTree(const vll &f) { build(f); } // create FT based on f

    FenwickTree(int m, const vi &s)
    { // create FT based on s
        vll f(m + 1, 0);
        for (int i = 0; i < (int)s.size(); ++i) // do the conversion first
            ++f[s[i]];                          // in O(n)
        build(f);                               // in O(m)
    }

    ll rsq(int j)
    { // returns RSQ(1, j)
        ll sum = 0;
        for (; j; j -= LSOne(j))
            sum += ft[j];
        return sum;
    }

    ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); } // inc/exclusion

    // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
    void update(int i, ll v)
    {
        for (; i < (int)ft.size(); i += LSOne(i))
            ft[i] += v;
    }

    int select(ll k)
    { // O(log m)
        int p = 1;
        while (p * 2 < (int)ft.size())
            p *= 2;
        int i = 0;
        while (p)
        {
            if (k > ft[i + p])
            {
                k -= ft[i + p];
                i += p;
            }
            p /= 2;
        }
        return i + 1;
    }
};

// 1-indexed
class RUPQ
{ // RUPQ variant
private:
    FenwickTree ft; // internally use PURQ FT
public:
    RUPQ(int m) : ft(FenwickTree(m)) {}
    /**
     * @brief Inclusive update: [ui, uj]
     * 
     * @param ui 
     * @param uj 
     * @param v 
     */
    void range_update(int ui, int uj, ll v)
    {
        ft.update(ui, v);                       // [ui, ui+1, .., m] +v
        ft.update(uj + 1, -v);                  // [uj+1, uj+2, .., m] -v
    }                                           // [ui, ui+1, .., uj] +v
    ll point_query(int i) { return ft.rsq(i); } // rsq(i) is sufficient
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> vs(n);
    for (auto &vv: vs) cin >> vv;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    RUPQ ft(n);
    vector<int> st(n), end(n);
    vector<int64_t> sm(n);
    int timer = 0;
    function<void(int,int,int64_t)> dfs = [&](int u, int p, int64_t cur) {
        st[u] = timer++;
        sm[st[u]] = cur + vs[u];
        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u, sm[st[u]]);
            }
        }
        end[u] = timer;
    };
    dfs(0, -1, 0);
    for (int i = 1; i <= n; i++) {
        ft.range_update(i, i, sm[i-1]);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            s--;
            int64_t before = vs[s];
            vs[s] = x;
            int64_t after = vs[s];
            int64_t diff = after - before;
            ft.range_update(st[s] + 1, end[s], diff);
        }
        else {
            assert(t == 2);
            int s;
            cin >> s;
            s--;
            int64_t ans = ft.point_query(st[s] + 1);
            cout << ans << '\n';
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

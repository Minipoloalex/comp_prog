#include <bits/stdc++.h>
using namespace std;

// Usage:
// FenwickTree ft(n);
// 1-indexed on n:
//      ft.rsq(1, n);
//      ft.update(n, v);

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

void solve() {
    int n;
    cin >> n;
    vector<int> c(n);
    for (auto &ci: c) cin >> ci;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> st(n), end(n), euler(n);
    int timer = 0;
    function<void(int,int)> dfs = [&](int u, int p) {
        euler[timer] = u;
        st[u] = timer++;
        for (int v: g[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        end[u] = timer;
    };
    dfs(0, -1);

    vector<array<int,3>> qs(n);
    for (int i = 0; i < n; i++) {
        qs[i] = {end[i] - 1, st[i], i}; // inclusive: [start, end] (for fenwick tree later)
    }
    sort(qs.begin(), qs.end());

    int qidx = 0;
    FenwickTree ft(n);
    map<int,int> last;  // last occurrence of the values (right-most occurrence)
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        int node = euler[i];
        int color = c[node];
        if (last.find(color) != last.end()) {
            // if color was already included
            ft.update(last[color], -1);
        }
        last[color] = i + 1;
        ft.update(last[color], 1);
        while (qidx < n && qs[qidx][0] == i) {
            // like answering queries
            auto &[e, s, orig_idx] = qs[qidx];
            int cnt = (int)ft.rsq(s+1, e+1);    // 1-indexing
            ans[orig_idx] = cnt;
            qidx++;
        }
    }
    for (int a: ans) cout << a << " ";
    cout << '\n';
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

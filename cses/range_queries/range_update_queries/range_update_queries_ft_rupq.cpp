#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S)) // the key operation

typedef long long ll; // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

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
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;

    RUPQ ft(n);
    for (int i = 1; i <= n; i++) {
        ft.range_update(i, i, x[i-1]);    // 1-indexed
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b, u;
            cin >> a >> b >> u;
            ft.range_update(a, b, u);   // 1-indexed
        }
        else {
            assert(t == 2);
            int k;
            cin >> k;
            cout << ft.point_query(k) << '\n';
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

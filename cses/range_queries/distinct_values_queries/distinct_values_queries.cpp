#include <bits/stdc++.h>
using namespace std;

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
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    vector<array<int,3>> qs(q);
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        qs[i] = {b, a, i};
    }
    sort(qs.begin(), qs.end());

    FenwickTree ft(n);
    map<int,int> mp;
    vector<int> ans(q);
    int idx = 0;
    for (int i = 0; i < n; i++) {
        // disable the previous value since:
        // it's not the most "lucrative" occurrence of this value (anymore) for our subarray queries. It's more to the left than what we just found
        if (mp.find(x[i]) != mp.end()) {
            ft.update(mp[x[i]], -1);
        }
        mp[x[i]] = i + 1;
        ft.update(mp[x[i]], 1);     // enable the value (the right-most occurrence we have found til now)
        while (idx < q && qs[idx][0] == i + 1) {    // go over the queries that finish in this index, getting the range sum of activated values that precede them
            auto &[b, a, orig_idx] = qs[idx];
            ans[orig_idx] = (int) ft.rsq(a,b);
            idx++;
        }
    }
    for (int a: ans) cout << a << '\n';
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

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
};

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto &x: p) cin >> x;

    int64_t ans = 0;
    FenwickTree ft(n);
    for (int i = 0; i < n; i++) {
        int pb = p[i];
        int smaller_than_b = 0;
        for (int j = n - 1; j > i; j--) {
            int pc = p[j];
            int64_t smaller_than_pc = ft.rsq(pc - 1);
            ans += smaller_than_b * smaller_than_pc;
            if (pb > pc) {
                smaller_than_b++;
            }
        }
        ft.update(pb, 1);
    }
    cout << ans << '\n';
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

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
    vector<int> p(n);
    set<int> s; // could instead erase with unique, but may still TLE with map: would require going to vectors only (with upper_bounds to handle BIT)
    for(auto &pi: p) {
        cin >> pi;
        s.insert(pi);
    }
    vector<array<int,3>> qs(q);
    for (auto &qi: qs) {
        char c;
        cin >> c;
        if (c == '!') {
            int k, x;
            cin >> k >> x;
            s.insert(x);
            qi = {k-1, x, 0};
        }
        else {
            assert(c == '?');
            int a, b;
            cin >> a >> b;
            s.insert(a);
            s.insert(b);
            qi = {a, b, 1};
        }
    }
    map<int,int> mp;
    int i = 1;  // fenwick tree is 1-indexed
    for (int sal: s) {
        mp[sal] = i++;
    }
    FenwickTree ft((int)s.size());
    for (auto &pi: p) {
        ft.update(mp[pi], 1);   // add 1 occurrence
    }

    for (auto &[a, b, type]: qs) {
        if (type == 0) {
            int prev = p[a];
            ft.update(mp[prev], -1);
            int nw = b;
            p[a] = nw;
            ft.update(mp[nw], 1);
        }
        else {
            int cnt = int(ft.rsq(mp[a], mp[b]));
            cout << cnt << '\n';
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

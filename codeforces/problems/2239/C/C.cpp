#include <bits/stdc++.h>
using namespace std;

// Usage:
// FenwickTree ft(n);
// 1-indexed on n:
// e.g. Sum[0:n-1] = ft.rsq(1, n);

#define LSOne(S) ((S) & -(S))

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

// 1-indexed
class FenwickTree
{ // index 0 is not used
private:
    vll ft;
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

    // 1-indexed: [1, j]
    ll rsq(int j)
    { // returns RSQ(1, j)
        ll sum = 0;
        for (; j; j -= LSOne(j))
            sum += ft[j];
        return sum;
    }

    // 1-indexed: [i, j]
    ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); }

    // updates value of the i-th element by v
    // 1-indexed: i
    void update(int i, ll v)
    {
        for (; i < (int)ft.size(); i += LSOne(i))
            ft[i] += v;
    }

    int select(ll k)
    {
        int p = 1;
        while (p * 2 < (int)ft.size())
            p *= 2;
        int i = 0;
        while (p)
        {
            if (i + p < (int)ft.size() && k > ft[i + p])
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
    vector<int64_t> ans(n);
    vector<pair<char,int64_t>> arr(n);
    for (auto &[c, val]: arr) {
        cin >> c >> val;
    }

    // Usage:
    FenwickTree ft(n);
    // 1-indexed on n:
    // e.g. Sum[0:n-1] = ft.rsq(1, n);

    for (int i = 1; i <= n; i++) {
        ft.update(i, 1);
    }
    int R = -1;
    int64_t cur = 0;
    for (int i = n - 1; i >= 0; i--) {
        auto &[c, val] = arr[i];
        if (c == 'p') {
            if (R != -1) {
                if (val < n) cur += ft.rsq(val + 1, n); // [val + 1, n), val is 1-indexed already
            }
            ans[i] = val;
            ft.update(val, -1);
        }
        else {
            assert(c == 's');
            if (R == -1) {
                R = i;
            }
            else {
                int L = i;
                int64_t sr = arr[R].second;
                int64_t sl = val;
                int n_left = L+2;
                int64_t tgt = sr - cur - sl - n_left;

                int lo = 1, hi = n_left;
                while (lo < hi) {
                    int med = lo + (hi - lo + 1) / 2;
                    int x = ft.select(med);

                    int64_t greater = 0; // values greater than x (inside the p's)
                    for (int j = L+1; j < R; j++) {
                        if (ans[j] > x) {
                           greater++;
                        }
                    }
                    int64_t smaller = R - (L + 1) - greater; // values smaller than x (inside the p's)
                    int64_t ret = greater - smaller - med;

                    if (ret < tgt) {
                        hi = med - 1;
                    }
                    else {
                        lo = med;
                    }
                }
                int x = ft.select(lo);
                ans[R] = x;
                ft.update(x, -1);

                R = L;
                cur = 0;
            }
        }
    }
    if (R != -1) ans[R] = ft.select(1);

    for (int64_t x: ans) {
        cout << x << " ";
    }
    cout << '\n';
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

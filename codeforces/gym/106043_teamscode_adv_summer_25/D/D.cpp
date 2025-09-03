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

    // 1-indexed: [1, j]
    ll rsq(int j)
    { // returns RSQ(1, j)
        ll sum = 0;
        for (; j; j -= LSOne(j))
            sum += ft[j];
        return sum;
    }

    // 1-indexed: [i, j]
    ll rsq(int i, int j) {
        if (i > j) return 0;
        return rsq(j) - rsq(i - 1);
    }

    // updates value of the i-th element by v
    // 1-indexed: i
    void update(int i, ll v)
    {
        for (; i < (int)ft.size(); i += LSOne(i))
            ft[i] += v;
    }
};

using Q = array<int,3>;

void solve() {
    int n, q, l;
    cin >> n >> q >> l;
    vector<int> r(n);
    for (auto &ri: r) cin >> ri;
    vector<int> val_to_freq(n + 1), first_idx(n + 1, INT_MAX);
    for (int i = 0; i < n; i++) {
        val_to_freq[r[i]]++;
        first_idx[r[i]] = min(first_idx[r[i]], i);
    }
    FenwickTree total(n), cnt(n);
    vector<vector<int>> freq_to_values(n + 1);
    for (int i = 0; i <= n; i++) {
        int freq = val_to_freq[i];
        if (freq) {
            freq_to_values[freq].push_back(i);
            cnt.update(first_idx[i] + 1,     +1);
            total.update(first_idx[i] + 1,   +freq);
        }
    }

    vector<Q> qs(q);
    for (int i = 0; i < q; i++) {
        int a, k;
        cin >> a >> k;
        qs[i] = {a, k, i};
    }

    sort(qs.begin(), qs.end());
    vector<int> ans(q);
    int curfreq = 0;
    for (int i = 0; i < q; i++) {
        auto &[a, k, origidx] = qs[i];
        while (curfreq <= a && curfreq <= n) {
            for (int val: freq_to_values[curfreq]) {
                total.update(first_idx[val] + 1, -curfreq);
                cnt.update(first_idx[val] + 1, -1);
            }
            curfreq++;
        }

        int first_to_remove = int(upper_bound(r.begin(), r.end(), k) - r.begin());
        int cnt_remove = n - first_to_remove;

        // [first_to_remove, n - 1] (0-indexed)
        int total_after_larger_than_a = int(total.rsq(1, n) - total.rsq(1, first_to_remove));
        int cnt_after_larger_than_a = int(cnt.rsq(1, n) - cnt.rsq(1, first_to_remove));
        cnt_remove -= (total_after_larger_than_a - a * cnt_after_larger_than_a);

        ans[origidx] = cnt_remove * 2 + a;
    }
    for (int v: ans) cout << v << '\n';
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

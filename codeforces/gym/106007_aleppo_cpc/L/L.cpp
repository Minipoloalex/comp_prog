#include <bits/stdc++.h>
using namespace std;

int calculate_answer(vector<pair<int,int>> &segs, int m) {
    int ans = 0, p = -1;
    for (auto &[l, r]: segs) {
        l = max(l, p + 1);
        int sz = max(r - l + 1, 0);
        ans += (sz + m - 1) / m;
        p = max(p, l + (sz + m - 1) / m * m - 1);
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    auto get_idx = [&](int value) {
        return int(lower_bound(vals.begin(), vals.end(), value) - vals.begin());
    };

    int sz = int(vals.size());

    bool all_equal = sz == 1;
    int q; cin >> q;
    int y = 0;
    int OR = 0;

    vector<vector<int>> occ(sz);
    vector<int> res(sz);
    for (int i = 0; i < n; i++) {
        OR |= a[i];
        int cidx = get_idx(a[i]);
        occ[cidx].push_back(i);
        for (int j = 0; j < 31; j++) {
            if ((a[i] & (1 << j)) != (a[0] & (1 << j))) {
                y |= (1 << j);
            }
        }
    }
    for (int i = 0; i < sz; i++) {
        vector<int> &v = occ[i];
        vector<pair<int,int>> segs;
        for (int j = 0; j < int(v.size()); j++) {
            int last = j > 0 ? v[j - 1] : -1;
            if (v[j] == last + 1) {
                continue;
            }
            else {
                segs.emplace_back(last + 1, v[j] - 1);
            }
        }
        if (v.back() != n - 1) {
            segs.emplace_back(v.back() + 1, n - 1);
        }
        res[i] = calculate_answer(segs, m);
    }

    while (q--) {
        int x;
        cin >> x;
        if (all_equal) {
            cout << "0\n";
            continue;
        }
        int A = x | OR;
        int ans;
        if ((x & y) != y) {
            ans = -1;
        }
        else {
            int residx = get_idx(A);
            if (residx == sz || vals[residx] != A) {
                ans = (n + m - 1) / m;
            }
            else {
                ans = res[residx];
            }
        }
        cout << ans << '\n';
    }
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

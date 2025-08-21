#include <bits/stdc++.h>
using namespace std;

vector<int64_t> compute(vector<int64_t> v) {
    int n = int(v.size());
    vector<int64_t> pref(n + 1);
    for (int i = 1; i <= n; i++) {
        pref[i] += pref[i - 1] + v[i - 1];
    }
    return pref;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int64_t> a(n), b(m);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    vector<int64_t> prefA = compute(a);
    vector<int64_t> prefB = compute(b);
    vector<pair<int,int>> chosen = {{0, 0}};
    int aidx = 0, bidx = 0;
    for (int z = 1; z <= n + m; z++) {
        if (aidx < n && bidx < m){
            if (a[aidx] >= b[bidx]) {
                aidx++;
            }
            else {
                bidx++;
            }
        }
        else if (aidx < n) {
            aidx++;
        }
        else {
            assert(bidx < m);
            bidx++;
        }
        chosen.emplace_back(aidx, bidx);    // here corresponds to size
    }
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        auto &[asize, bsize] = chosen[z];
        int64_t ans = 0;
        if (asize > x) {
            // take x
            ans += prefA[x];
            ans += prefB[z - x];
        }
        else if (bsize > y) {
            ans += prefB[y];
            ans += prefA[z - y];
        }
        else {
            ans += prefA[asize];
            ans += prefB[bsize];
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

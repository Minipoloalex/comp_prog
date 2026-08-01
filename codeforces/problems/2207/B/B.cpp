#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    vector<int> d(m);
    int aidx = 0;
    for (int i = 1; i <= l; i++) {
        // need to know how many more resets there are: these is the nth maximum that I need to add to
        // e.g. m=10, resets=5, add to 6th maximum: (m-1 - resets)
        int remresets = n - aidx;
        // int nth_max_id = max(0, min(m-1, m-1-remresets));
        // sort(d.begin(), d.end()); // unnecessary but easier
        // d[nth_max_id]++;

        // nth_element(d.begin(), d.begin() + nth_max_id, d.end()); // partial sorting only
        // d[nth_max_id]++;

        // could have also sorted (partial sorting) based on greater():
        nth_element(d.begin(), d.begin() + min(remresets, m-1), d.end(), greater());
        d[min(remresets, m-1)]++;

        if (aidx < n && i == a[aidx]) {
            *max_element(d.begin(), d.end()) = 0;
            aidx++;
        }
    }
    int ans = *max_element(d.begin(), d.end());
    cout << ans << '\n';
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

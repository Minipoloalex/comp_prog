#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    vector<int64_t> prefa(n), prefb(n);
    for (int i = 0; i < n; i++) {
        int v = a[i] == '0' ? 1 : -1;
        prefa[i] = v;
        if (i > 0) prefa[i] += prefa[i - 1];
    }
    for (int i = 0; i < n; i++) {
        int v = b[i] == '1' ? 1 : -1;
        prefb[i] = v;
        if (i > 0) prefb[i] += prefb[i - 1];
    }
    int64_t ans = int64_t(n) * n * (n+1) / 2;
    int64_t sub = 0;
    sort(prefa.begin(), prefa.end());
    sort(prefb.begin(), prefb.end());
    for (int i = 0; i < n; i++) {
        // add for every smaller value, subtract for greater or equal
        int idx = int(lower_bound(prefb.begin(), prefb.end(), prefa[i]) - prefb.begin());
        int cnt = idx;
        sub += prefa[i] * cnt;
        sub -= prefa[i] * (n - cnt);
    }
    for (int i = 0; i < n; i++) {
        // add for smaller or equal and subtract for every greater
        int idx = int(upper_bound(prefa.begin(), prefa.end(), prefb[i]) - prefa.begin());
        int cnt = idx;
        sub += prefb[i] * cnt;
        sub -= prefb[i] * (n - cnt);
    }
    // cout << ans << " " << sub << " ";
    ans -= sub/2;
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

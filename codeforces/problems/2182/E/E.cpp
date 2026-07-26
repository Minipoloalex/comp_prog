#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    int64_t k;
    cin >> n >> m >> k;
    vector<int> a(m);
    for (auto &x: a) cin >> x;
    sort(a.begin(), a.end());
    vector<pair<int,int>> f(n);
    for (auto &[ai, bi]: f) {
        int xi, yi, zi;
        cin >> xi >> yi >> zi;
        k -= yi;
        ai = xi;
        bi = zi - yi;
    }
    sort(f.begin(), f.end());
    priority_queue<int> pq;
    int ans = 0;
    int i = 0;
    for (int j = 0; j < m; j++) {
        while (i < n && f[i].first <= a[j]) {
            pq.push(f[i++].second);
        }
        if (!pq.empty()) {
            ans++;
            pq.pop();
        }
    }
    while (i < n) { // the remaining ones that cannot be happy from available boxes
        pq.push(f[i++].second);
    }
    vector<int> rem; rem.reserve(n);
    while (!pq.empty()) {
        rem.push_back(pq.top());
        pq.pop();
    }
    reverse(rem.begin(), rem.end());
    for (int val: rem) {
        if (k - val < 0) break;
        k -= val;
        ans++;
    }
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, l, x, y;
    cin >> n >> m >> l >> x >> y;
    vector<pair<int,int>> bus(n);
    for (auto &[si, ti]: bus) {
        cin >> si >> ti;
    }
    vector<int> p(m);
    for (auto &pi: p) cin >> pi;

    // for each person, find the bus that starts before it (<=) that leads to the best time

    sort(bus.begin(), bus.end());
    vector<int> st(n);
    for (int i = 0; i < n; i++) st[i] = bus[i].first;
    vector<double> busans(n);
    for (int i = 0; i < n; i++) {
        auto &[si, ti] = bus[i];
        busans[i] = double(ti - si) / x + double(l - ti) / y;
    }
    vector<double> pfmin(n+1, DBL_MAX);
    for (int i = 0; i < n; i++) {
        pfmin[i+1] = min(pfmin[i], busans[i]);
    }

    cout << fixed << setprecision(10);
    for (int i = 0; i < m; i++) {
        // index of first bus not available to person i
        int lstbusid = int(upper_bound(st.begin(), st.end(), p[i]) - st.begin());
        // minimum from buses available to person
        double buscur = pfmin[lstbusid];
        double walk = double(l - p[i]) / y;
        
        double ans = min(walk, buscur);
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

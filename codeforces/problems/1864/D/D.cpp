#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (auto &s: g) cin >> s;
    int ans = 0;
    vector<pair<int,int>> curd(n, {0,0});
    for (int i = 0; i < n; i++) {
        vector<pair<int,int>> nxtd(n, {0,0});
        vector<int> pref(n + 1);
        for (int j = 0; j < n; j++) {
            pref[j + 1] = pref[j] + curd[j].first - curd[j].second;
        }
        for (int j = 0; j < n; j++) {
            int v = g[i][j] - '0';
            if ((pref[j + 1] + v) % 2 == 1) {
                ans++;
                curd[j].first++;
                if (j + 1 < n) curd[j + 1].second++;
            }
        }
        nxtd[0].first += curd[0].first;
        for (int j = 0; j < n; j++) {
            if (j + 1 < n) nxtd[j].first += curd[j + 1].first;
            if (j - 1 >= 0) nxtd[j].second += curd[j - 1].second;
        }
        curd = nxtd;
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

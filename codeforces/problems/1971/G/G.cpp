#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    map<int,pair<vector<int>,vector<int>>> mp;
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int d = a[i] / 4;
        mp[d].first.push_back(a[i]);
        mp[d].second.push_back(i);
    }
    for (auto &[d, p]: mp) {
        auto &[vals, ids] = p;
        sort(ids.begin(), ids.end());
        sort(vals.begin(), vals.end());
        for (int i = 0; i < int(ids.size()); i++) {
            ans[ids[i]] = vals[i];
        }
    }
    for (int v: ans) {
        cout << v << " ";
    }
    cout << '\n';
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

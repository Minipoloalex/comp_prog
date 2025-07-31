#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto &pi: p) cin >> pi;
    vector<int> ans(n);
    bool use_odd = true;
    for (int i = 1; i < n; i += 2) {
        if (p[i] == 1) {
            use_odd = false;
        }
    } 
    int st = use_odd ? 1 : 2;
    vector<pair<int,int>> use, others;
    for (int i = 0; i < n; i++) {
        if (i >= st && i < n - 1 && (i - st) % 2 == 0) {
            use.emplace_back(p[i], i);
        }
        else {
            others.emplace_back(p[i], i);
        }
    }
    sort(use.begin(), use.end());
    int cur = n;
    for (auto &[v, i]: use) {
        ans[i] = cur--;
    }
    sort(others.begin(), others.end());
    for (auto &[v, i]: others) {
        ans[i] = cur--;
    }
    for (int v: ans) cout << v << " ";
    cout << '\n';
    // for (int i = 0; i < n; i++) {
    //     cout << p[i] + ans[i] << " ";
    // }
    // cout << '\n';
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

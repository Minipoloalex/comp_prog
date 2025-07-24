#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> ans;
    for (int i = (k + 1) / 2; i < n - k / 2; i++) {
        ans.push_back(a[i]);
    }
    if (k % 2 == 1) {
        reverse(ans.begin(), ans.end());
    }
    for (int v: ans) cout << v << " ";
    cout << '\n';
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

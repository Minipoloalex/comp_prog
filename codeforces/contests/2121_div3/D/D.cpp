#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    vector<pair<int,int>> ans;
    for (int i = 0; i < n; i++) {
        auto it = min_element(a.begin() + i, a.end());
        int idx = int(it - a.begin());
        for (int j = idx - 1; j >= i; j--) {
            swap(a[j], a[j + 1]);
            ans.emplace_back(1, j);
        }
    }
    for (int i = 0; i < n; i++) {
        auto it = min_element(b.begin() + i, b.end());
        int idx = int(it - b.begin());
        for (int j = idx - 1; j >= i; j--) {
            swap(b[j], b[j + 1]);
            ans.emplace_back(2, j);
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) {
            swap(a[i], b[i]);
            ans.emplace_back(3, i);
        }
    }
    cout << ans.size() << '\n';
    for (auto &[type, i]: ans) {
        cout << type << " " << i + 1 << '\n';
    }
    for (int i = 0; i + 1 < n; i++) {
        assert(a[i] < a[i + 1]);
        assert(b[i] < b[i + 1]);
        assert(a[i] < b[i]);
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

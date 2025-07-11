#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, j, k;
    cin >> n >> j >> k;
    j--;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    bool ans = false;
    if (k >= 2) {
        ans = true;
    }
    else {
        ans = a[j] == *max_element(a.begin(), a.end());
    }
    cout << (ans ? "YES": "NO") << '\n';
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

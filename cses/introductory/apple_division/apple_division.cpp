#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int64_t total = accumulate(a.begin(), a.end(), 0LL);
    int64_t mn = INT64_MAX;
    for (int i = 1; i < (1 << n); i++) {
        int64_t sm = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                sm += a[j];
            }
        }
        int64_t diff = abs((total - sm) - sm);
        mn = min(diff, mn);
    }
    cout << mn << '\n';
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

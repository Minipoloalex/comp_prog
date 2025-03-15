#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto &y: a) cin >> y;
    int mn = *min_element(a.begin(), a.end());
    int mx = *max_element(a.begin(), a.end());
    int64_t def = 0;
    for (int i = 0; i < n - 1; i++) {
        def += abs(a[i] - a[i + 1]);
    }
    int fst = a.front(), lst = a.back();
    int large = max(fst, lst);
    int small = min(fst, lst);
    int64_t ansb = INT64_MAX, anss = INT64_MAX;
    if (mx < x) {
        // use large
        ansb = x - large;
    }
    if (mn > 1) {
        // use small
        anss = small - 1;
    }
    for (int i = 0; i < n - 1; i++) {
        int64_t s = min(a[i], a[i + 1]);
        int64_t b = max(a[i], a[i + 1]);
        if (mx < x) {
            ansb = min(ansb, (x - b) * 2);
        }
        if (mn > 1) {
            anss = min(anss, (s - 1) * 2);
        }
    }
    int64_t ans = (ansb != INT64_MAX ? ansb : 0) + (anss != INT64_MAX ? anss : 0) + def;
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

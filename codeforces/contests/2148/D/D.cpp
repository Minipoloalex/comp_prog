#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> odds;
    int64_t evens = 0;
    for (int v: a) {
        if (v % 2 == 0) {
            evens += v;
        }
        else {
            odds.push_back(v);
        }
    }
    int64_t ans = 0;
    sort(odds.begin(), odds.end());
    if (!odds.empty()) {
        ans += evens;
        int l = 0, r = int(odds.size()) - 1;
        while (l <= r) {
            ans += odds[r--];
            l++;
        }
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

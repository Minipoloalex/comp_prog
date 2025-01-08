#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> movies(n);
    for (auto &[r, l]: movies) cin >> l >> r;
    sort(movies.begin(), movies.end());
    int ans = 0;
    multiset<int> prev;
    for (auto &[r, l]: movies) {
        int cur = int(prev.size());
        if (!prev.empty() && l >= *prev.begin()) {
            ans++;
            auto it = prev.upper_bound(l);
            prev.erase(--it);
            prev.insert(r);
        }
        else if (cur < k) {
            prev.insert(r);
            ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

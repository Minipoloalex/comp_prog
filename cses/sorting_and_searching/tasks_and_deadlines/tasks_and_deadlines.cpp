#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> tasks(n);
    for (auto &[a, d]: tasks) cin >> a >> d;
    sort(tasks.begin(), tasks.end());

    int64_t ans = 0, cur = 0;
    for (auto &[a, d]: tasks) {
        cur += a;
        ans += d - cur;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

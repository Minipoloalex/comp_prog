#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    int ans = 0, cnt = 0;

    vector<bool> light(n, true);
    for (int i = 0; i <  k; i++) {
        int x; cin >> x;

        int delta = 0;
        for (int it = x - 1; it < n; it += x) {
            if (light[it]) delta++;
            else delta--;
            light[it] = !light[it];
        }

        cnt += delta;
        ans = max(ans, cnt);
    }

    cout << ans << endl;
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

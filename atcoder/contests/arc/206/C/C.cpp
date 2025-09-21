#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 998244353;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    int64_t ans = 0;
    int found = -1;
    for (int i = 1; i <= n; i++) {
        if (a[i] == -1) continue;
        // if (a[i] != i - 1 && a[i] != i + 1) {
        //     found = i;
        //     break;
        // }
        if (a[i] < i - 1 || a[i] > i + 1 || a[i] == i) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        ans = 1;
        for (int i = 1; i <= n; i++) {
            if (i == found) continue;
            int need = i < found ? i + 1 : i - 1;
            if (a[i] != -1 && a[i] != need) {
                ans = 0;
                break;
            }
        }
    }
    else {
        // find right most value that has: a[i] = i + 1
        // find left most value that has: a[i] = i - 1
        // in between, we'll have to do some stuff
        int lef = 0;
        int rig = n + 1;
        for (int i = 1; i <= n; i++) {
            if (a[i] == -1) continue;
            if (a[i] == i + 1) {
                lef = max(lef, i);
            }
            if (a[i] == i - 1) {
                rig = min(rig, i);
            }
        }
        if (rig > lef) {
            // valid
            int cnt_in_between = rig - lef - 1;
            ans = (1LL * cnt_in_between * (n - 1) + 1) % MOD;
        }
    }
    cout << ans << '\n';
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

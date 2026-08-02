#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, h;
    cin >> n >> h;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    int64_t ans = h-a[0];

    // lef[i][j]: for point i, what is the answer from [j, i] (j <= i)
    // rig[i][j]: for point i, what is the answer from [i, j] (i <= j)
    vector<vector<int64_t>> lef(n, vector<int64_t>(n)), rig(n, vector<int64_t>(n));
    for (int i = 0; i < n; i++) {
        int64_t cursm = 0;
        int curmx = 0;
        for (int j = i; j < n; j++) {
            curmx = max(curmx, a[j]);
            cursm += h - curmx;
            rig[i][j] = cursm;
        }
        curmx = 0;
        cursm = 0;
        for (int j = i; j >= 0; j--) {
            curmx = max(curmx, a[j]);
            cursm += h - curmx;
            lef[i][j] = cursm;
        }
    }

    for (int i = 0; i < n; i++) {
        int midmx_id = -1;
        int midmx = 0;
        for (int j = i+1; j < n; j++) {
            // int mx = max(a[i], a[j]);
            // int mn = min(a[i], a[j]);
            int mxid = i, mnid = j;
            if (a[i] < a[j]) {
                swap(mxid, mnid);
            }
            int mx = a[mxid];
            int64_t curans = 0;
            if (midmx <= mx) {
                // use the min completely
                curans = lef[mnid][0] + rig[mnid][n-1] - (h - a[mnid]);
            }
            else {
                // use both till the middle max
                curans = lef[i][0] + rig[i][midmx_id] + rig[j][n-1] + lef[j][midmx_id] - (h - a[midmx_id]) - (h - a[i]) - (h - a[j]);
            }

            if (a[j] > midmx) {
                midmx_id = j;
                midmx = a[j];
            }
            ans = max(ans, curans);
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

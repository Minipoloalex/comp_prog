#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t k;
    cin >> k;
    vector<int> ans;
    while (k > 0) {
        int64_t mx = 0;
        int best = -1;
        for (int i = 1; i <= k; i++) {
            int64_t total = int64_t(1 + i) * i / 2;
            if (total > k) {
                break;
            }
            best = i;
            mx = total;
        }
        // cout << k << " " << best << " " << mx << endl;
        k -= mx;
        assert(best != -1);
        ans.push_back(best);
    }
    int cnt = int(accumulate(ans.begin(), ans.end(), 0) + ans.size());
    cout << cnt << '\n';
    int xc = 0, yc = 0;
    for (int i: ans) {
        for (int j = 0; j <= i; j++) {
            cout << xc << " " << yc << '\n';
            yc++;
        }
        xc++;
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

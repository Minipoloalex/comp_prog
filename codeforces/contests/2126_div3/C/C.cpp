#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    k--;
    vector<int> h(n);
    for (auto &hi: h) cin >> hi;
    
    int curh = h[k], curw = 1;
    sort(h.begin(), h.end());
    int mx = h[n-1];
    bool ans = true;
    while (curh < mx) {
        // max height we can jump to:
        int max_steps = curh - curw + 1;
        int max_new_height = curh + max_steps;
        int idx = int(upper_bound(h.begin(), h.end(), max_new_height) - h.begin() - 1);
        if (curh == h[idx]) {
            ans = false;
            break;
        }
        curw += h[idx] - curh;
        curh = h[idx];

        // if (curh < curw) {
        //     ans = false;
        //     break;
        // }
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

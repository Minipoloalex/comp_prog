#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a;
    bool zero = true;   // grab first zero
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        if (zero || ai != 0) {
            a.push_back(ai);
            if (ai == 0) zero = false;
        }
    }
    int ans = int(a.size());
    n = int(a.size());

    vector<int> sufmex(n);
    vector<bool> have(n + 1);
    int cur = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] <= n) have[a[i]] = true;
        while (have[cur]) {
            cur++;
        }
        sufmex[i] = cur;
    }

    bool valid = true;
    int mn = INT_MAX;
    for (int i = 0; i < n - 1; i++) {
        mn = min(mn, a[i]);
        if (mn < sufmex[i + 1]) {
            valid = false;
        }
    }
    if (!valid) {
        ans--;  // just remove the 0 we chose
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

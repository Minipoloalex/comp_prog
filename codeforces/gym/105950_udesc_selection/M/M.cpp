#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t n, a, b;
    cin >> n >> a >> b;
    vector<int64_t> h(n, 0);
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        if (i == 0) continue;
        h[i] = h[i - 1] + ai;
    }
    int k;
    cin >> k;
    k--;
    int64_t mx_idx = -1, mx = INT64_MIN;
    for (int i = 0; i < n; i++) {
        if (i == k) continue;
        if (h[i] > mx) {
            mx = h[i];
            mx_idx = i;
        }
    }
    int64_t h1 = h[k] + b;
    int64_t h2 = h[mx_idx] + a;
    if (h2 >= h1) {
        cout << "SIM\n";
        cout << mx_idx + 1 << '\n';
    }
    else {
        cout << "NAO\n";
    }
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

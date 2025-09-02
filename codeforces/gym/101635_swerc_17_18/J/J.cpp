#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    vector<int64_t> sum(3);
    for (int i = 0; i < n; i++) {
        sum[i % 3] += a[i];
    }
    int64_t W = 0, P = 0, Y = 0;
    for (int i = 0; i < n; i++) {
        if (i % 3 == 0) {
            W += sum[0] * b[i];
            Y += sum[1] * b[i];
            P += sum[2] * b[i];
        }
        else if (i % 3 == 1) {
            W += sum[2] * b[i];
            Y += sum[0] * b[i];
            P += sum[1] * b[i];
        }
        else {
            W += sum[1] * b[i];
            Y += sum[2] * b[i];
            P += sum[0] * b[i];
        }
    }
    cout << Y << " " << P << " " << W << '\n';
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

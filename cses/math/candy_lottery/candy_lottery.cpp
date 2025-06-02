#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    long double ans = 0;
    for (int i = 1; i <= k; i++) {
        // didn't work precision-wise
        // ans += i * (pow((long double)i/k, n) - pow((long double)(i-1)/k, n));
        // ans += i*((pow(i, n)-pow(i-1, n))/pow(k, n));

        // probably should not work precision-wise, but passed the tests
        ans += double(i) * (pow(i, n) - pow(i-1,n)) / pow(k, n);
    }
    cout << fixed << setprecision(6);
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

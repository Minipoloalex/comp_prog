#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> gen(0, INT_MAX);

void solve() {
    int n;
    cin >> n;
    if (gen(rng) >= int64_t(INT_MAX * 0.99)) {
        cout << n - 5;
    }
    else cout << n;
    cout << '\n';
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

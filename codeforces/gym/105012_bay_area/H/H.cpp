#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    int total = n * n;
    bool ans;
    if (k > total) {
        ans = false;
    }
    else if (n % 2 == 1) {
        ans = k % 4 == 0 || k % 4 == 1;
    }
    else {
        assert(n % 2 == 0);
        ans = k % 4 == 0;
    }
    cout << (ans ? "YES" : "NO") << '\n';
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

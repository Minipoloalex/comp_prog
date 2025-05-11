#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, p, q;
    cin >> n >> m >> p >> q;
    string ans;
    if (n % p == 0) {
        int aux = n / p;
        int sm = aux * q;
        if (sm == m) {
            ans = "YES";
        }
        else {
            ans = "NO";
        }
    }
    else {
        ans = "YES";
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

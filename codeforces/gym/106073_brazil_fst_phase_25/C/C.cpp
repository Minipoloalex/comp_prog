#include <bits/stdc++.h>
using namespace std;

void solve() {  
    int n; cin >> n;
    int lim = 42;
    vector<int> a(lim);

    int ones = 0;
    for (int i = 0; i <= n; i++) {
        cin >> a[n - i];
        ones += a[n - i];
    }

    int op = 0;

    while (!(ones == 1 && a[0])) {
        if (a[0]) {
            for (int i = lim - 2; i >= -1; i--) {
                if (i == -1 || a[i]) {
                    a[i+1] ^= 1;
                    a[i+1] ? ones++ : ones--;
                }
            }
        } else {
            for (int i = 1; i < lim; i++) {
                if (a[i]) {
                    a[i] = 0;
                    a[i-1] = 1;
                }
            }
        }
        op++;
    }

    cout << op << '\n';
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;

    if (n == 1) {
        cout << "1\n";
        return;
    }

    vector<int> ans(n + 1);
    if (n % 2 == 0) {
        ans[1] = 1;
        ans[n/2 + 1] = 2;

        int cur = n;
        for (int i = 2; i <= n / 2; i++) 
            ans[i] = cur--;

        for (int i = n/2 + 2; i <= n; i++) 
            ans[i] = cur--;

        for (int i = 1; i <= n; i++) {
            cout << ans[i] << " \n"[i==n];
        }
    } else {
        ans[1] = 1;
        ans[n/2 + 1] = n;
        ans[n] = 2;

        int cur = n - 1;
        for (int i = 2; i <= n / 2; i++) 
            ans[i] = cur--;

        for (int i = n/2 + 2; i < n; i++) 
            ans[i] = cur--;

        for (int i = 1; i <= n; i++) {
            cout << ans[i] << " \n"[i==n];
        }
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

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (auto &ai: a) cin >> ai;

        int mx = INT_MIN, mn = INT_MAX;
        for (int i = 0; i < n; i++) {
            mx = max(mx, a[i]);
            mn = min(mn, a[i]);
        }

        if (n == 1) cout << "0\n";
        else {
            cout << (0LL + mx - mn) * (n - 1) << '\n';
        }
    }
    return 0;
}

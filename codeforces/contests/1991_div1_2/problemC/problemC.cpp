#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        bool possible = true;
        for (int i = 1; i < n && possible; i++) {
            if ((a[i] & 1) != (a[i - 1] & 1)) possible = false;
        }
        if (!possible) {
            cout << "-1\n";
            continue;
        }

        // all numbers even or all numbers odd
        // all numbers [0, 2 ^ 30]
        cout << "31\n";
        for (int i = 29; i >= 0; i--) {
            // all numbers <= 2 ^ (i+1)
            // After choosing x = 2 ^ i, all numbers will be <= 2 ^ i
            int op = (1 << i);
            cout << op << " ";
            a[0] = abs(op - a[0]);
        }
        if (a[0] == 1) cout << 1;
        else cout << 0;

        cout << '\n';
    }
    return 0;
}

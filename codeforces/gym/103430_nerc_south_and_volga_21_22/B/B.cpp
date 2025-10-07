#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, a, b;
    cin >> n >> a >> b;

    int h = n / 2;
    if (a == h + 1 && b == h) {
        for (int i = n; i >= 1; i--) cout << i << ' ';
        cout << '\n';
    } else if (a <= h && b >= h + 1) {
        cout << a;

        for (int i = h + 1; i <= n; i++) {
            if (i == b) continue;
            cout << ' ' << i;
        }

        cout << ' ' << b;

        for (int i = 1; i <= h; i++) {
            if (i == a) continue;
            cout << ' ' << i;
        }
        cout << "\n";
    } else {
        cout << "-1\n";
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

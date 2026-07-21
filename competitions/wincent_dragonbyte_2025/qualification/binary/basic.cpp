#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n == 2) {
        cout << "-1\n";
        return;
    }
    auto possible = [&](int b) {
        int nn = n;
        while (nn) {
            int d = nn % b;
            if (d > 1) {
                return false;
            }
            nn /= b;
        }
        return true;
    };
    for (int i = 3; i <= max(3, n); i++) {
        if (possible(i)) {
            cout << i << '\n';
            return;
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

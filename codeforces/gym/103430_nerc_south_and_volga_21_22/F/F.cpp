#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t a, b, x;
    cin >> a >> b >> x;
    if (a < b) swap(a, b);

    while (x <= a && b != 0) {
        int64_t bp = a - b;
        if (((a - x) % b == 0) || ((bp > 0) && (a - x) % bp == 0)) {
            cout << "YES\n";
            return;
        }
        
        b = min(b, bp);
        if (b != 0) {
            a = a % b;
            swap(a, b);
        }
    }
    cout << "NO\n";
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

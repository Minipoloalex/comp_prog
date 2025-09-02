#include <bits/stdc++.h>
using namespace std;

void solve() {  
    int n; cin >> n;
    string st; cin >> st;
    
    int64_t p = 0, m = 0;
    for (char c : st) {
        if (c == '+') p++;
        else m++;
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int64_t a, b; cin >> a >> b;
        if (a < b) swap(a, b);

        int64_t sum = a * (p - m);
        int64_t d = a - b;

        if (sum == 0) cout << "YES\n";
        else if (d == 0) cout << "NO\n";
        else if (sum > 0) {
            // replace in + signs
            if (sum % d == 0 && p >= (sum / d)) cout << "YES\n";
            else cout << "NO\n";
        } else {
            sum = -sum;
            // replace in - signs
            if (sum % d == 0 && m >= (sum / d)) cout << "YES\n";
            else cout << "NO\n";
        }
    }
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

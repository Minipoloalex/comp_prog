#include <bits/stdc++.h>
using namespace std;

void solve() {
    int q;
    cin >> q;
    while (q--) {
        int64_t k;
        cin >> k;
        if (k <= 9) {
            cout << k << '\n';
            continue;
        }
        int64_t cur = 9, len = 1;
        while (k - cur * len > 0) {
            k -= cur * len;
            cur *= 10;
            len++;
        }
        // to easily understand this, run through examples where the last numbers are 1e5, 1e5 + 1, 1e5 + 2
        int64_t last_nr = cur / 9 + (k - 1) / len;
        int64_t last_digit_idx = (k - 1) % len;
        string s = to_string(last_nr);
        cout << s[last_digit_idx] << '\n';
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

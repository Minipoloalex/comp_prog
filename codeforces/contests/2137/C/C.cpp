#include <bits/stdc++.h>
using namespace std;

void solve() {
    int64_t a, b;
    cin >> a >> b;
    int64_t ans = -1;
    if ((a + b) % 2 == 0) ans = a + b;
    int64_t possible = a * b;
    if ((possible + 1) % 2 == 0) {
        ans = possible + 1;
    }
    else {
        for (int i = 2; i < 30; i++) {
            if (b % i == 0) {
                int64_t op1 = b / i + a * i;
                int64_t op2 = i + a * (b / i);
                if (op1 % 2 == 0) {
                    ans = max(ans, op1);
                }
                if (op2 % 2 == 0) {
                    ans = max(ans, op2);
                }
            }
        }
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

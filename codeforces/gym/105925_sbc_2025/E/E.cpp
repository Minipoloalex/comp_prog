#include <bits/stdc++.h>
using namespace std;

vector<int64_t> factor(int64_t n) {
    vector<int64_t> r;

    for (int64_t i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                r.push_back(i);
                n /= i;
            }
        }
    }

    if (n != 1) r.push_back(n);
    return r;
}

void solve() {  
    int64_t y, k;
    cin >> y >> k;

    auto factors = factor(y);
    int64_t x = 1, pf = 1;

    for (int64_t f : factors) {
        pf *= f;

        int64_t steps = (pf - x) / x;

        if (steps >= k) {
            cout << x * (k + 1) << '\n';
            return;
        } else {
            x = pf;
            k -= steps;
        }
    }

    cout << x * (k + 1) << '\n';
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

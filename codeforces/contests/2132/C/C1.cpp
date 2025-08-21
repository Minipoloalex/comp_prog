#include <bits/stdc++.h>
using namespace std;

vector<int64_t> pows;

void precompute() {
    pows.assign(21, 1);
    for (int i = 1; i <= 20; i++) {
        pows[i] = pows[i - 1] * 3;
    }
}

int64_t cost(int64_t x) {
    if (x == 0) {
        return 3;    
    }
    return pows[x + 1] + x * pows[x - 1];
}

void solve() {
    int n;
    cin >> n;

    int bit = 0;
    int64_t ans = 0;
    while (n) {
        int digit = n % 3;
        ans += digit * cost(bit++);
        n /= 3;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    precompute();
    while (t--) {
        solve();
    }
    return 0;
}

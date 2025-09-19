#include <bits/stdc++.h>
using namespace std;

const int MAX = int(1e6);
int64_t a[MAX + 1], b[MAX + 1];

const int64_t MOD = int64_t(1e9) + 7;

void precompute() {
    a[1] = b[1] = 1;
    for (int i = 2; i <= MAX; i++) {
        a[i] = 2*a[i-1] + b[i-1];
        b[i] = a[i-1]   + 4*b[i-1];
        a[i] %= MOD;
        b[i] %= MOD;
    }
}

void solve() {
    int n;
    cin >> n;
    cout << (a[n] + b[n]) % MOD << '\n';
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

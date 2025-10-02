#include <bits/stdc++.h>
using namespace std;

const int MOD = int(1e9) + 7;
const int MAX_N = int(1e6);
const int LOG = 20;

int sos[1 << LOG];
int pow2[MAX_N + 1];

void precompute() {
    pow2[0] = 1;
    for (int i = 1; i <= MAX_N; i++) {
        pow2[i] = (pow2[i-1] * 2) % MOD;
    }
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        sos[ai]++;
    }
    for (int i = 0; i < LOG; i++) {
        for (int mask = 0; mask < (1 << LOG); mask++) {
            if (mask & (1 << i)) {
                // this never exceeds n
                sos[mask ^ (1 << i)] += sos[mask];  // include supersets
            }
        }
    }
    for (int mask = 0; mask < (1 << LOG); mask++) {
        sos[mask] = pow2[sos[mask]] - 1;
    }
    for (int i = 0; i < LOG; i++) {
        for (int mask = 0; mask < (1 << LOG); mask++) {
            if (mask & (1 << i)) {
                sos[mask ^ (1 << i)] -= sos[mask];  // exclude supersets
                sos[mask ^ (1 << i)] %= MOD;
            }
        }
    }
    cout << (sos[0] + MOD) % MOD << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    precompute();
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

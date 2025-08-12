#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;
const int MAX = int(1e6);
int64_t fib[MAX + 1];

void solve() {
    int64_t n, k;
    cin >> n >> k;
    if (k == 1) {
        cout << n % MOD << '\n';
        return;
    }
    fib[1] = fib[2] = 1;
    int fst = -1, snd = -1;
    bool first = true;

    // according to editorial
    // turns out that we are in a cycle in at most k * 6
    for (int i = 3; i <= k * 7; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % k;
        if (fib[i] == 0) {
            if (first) {
                fst = i;
                first = false;
            }
            else {
                snd = i;
                break;
            }
        }
    }
    assert(fst != -1 && snd != -1);
    // cout << fst << " " << snd << " ";
    int diff = snd - fst;

    // want n-th number
    // first number + diff * (n - 1): because of cycles in fibonacci sequence modulo k

    int64_t ans = (fst % MOD + (((n - 1) % MOD) * (diff % MOD) % MOD)) % MOD;
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

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int64_t mod_exp(int64_t a, int64_t b, int64_t m) {
    if (b == 0) return 1;
    if (b & 1) return (a * mod_exp(a, b - 1, m)) % m;
    int64_t aux = mod_exp(a, b / 2, m);
    return (aux * aux) % m;
}
int64_t mod_inv(int64_t a, int64_t m) {
    return mod_exp(a, m - 2, m);
}

void solve() {
    int q;
    cin >> q;
    queue<pair<int,int>> f;
    pair<int64_t, int64_t> cur = {1, 0};
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int a, b;
            cin >> a >> b;
            f.emplace(a, b);
            (cur.first *= a) %= MOD;
            (cur.second *= a) %= MOD;
            (cur.second += b) %= MOD;
        }
        else if (t == 1) {
            auto [a, b] = f.front();
            f.pop();
            (cur.first *= mod_inv(a, MOD)) %= MOD;
            cur.second = (((cur.second - cur.first * b) % MOD) + MOD) % MOD;
        }
        else {
            assert(t == 2);
            int x;
            cin >> x;
            int64_t ans = ((cur.first * x) % MOD + cur.second) % MOD;
            cout << ans << '\n';
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

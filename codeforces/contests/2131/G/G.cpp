#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = int64_t(1e9) + 7;
const int MAX = int(1e6);

int64_t value[MAX + 1];

void precompute() {
    int64_t pref = 1;
    for (int i = 1; i <= MAX; i++) {
        int64_t cur = pref * i % MOD;
        value[i] = cur;
        pref = pref * cur % MOD;
    }
}

int cost(int64_t m) {
    if (m > 30) {
        return INT_MAX;
    }
    else {
        return 1 << (m - 1);
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> s(n);
    for (auto &si: s) cin >> si;
    sort(s.begin(), s.end());
    int64_t ans = 1;
    int i = 0;
    for (; i < n; i++) {
        if (cost(s[i]) > k) {
            break;
        }
        else {
            k -= cost(s[i]);
            ans = ans * value[s[i]] % MOD;
        }
    }
    if (k > 0) {
        int m = s[i];
        while (k > 0) {
            k--;
            ans = ans * m % MOD;
            if (k == 0) break;
            // cover as much as possible from m
            for (int j = 1; j < m; j++) {
                if (cost(j) > k) {
                    m = j;
                    break;
                }
                else {
                    ans = ans * value[j] % MOD;
                    k -= cost(j);
                }
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    precompute();
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

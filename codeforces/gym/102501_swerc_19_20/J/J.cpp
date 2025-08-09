#include <bits/stdc++.h>
using namespace std;

const int64_t mod = 1000000007;

int64_t powmod(int64_t a, int64_t b, int64_t p = mod) {   // a^b % p
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * powmod(a, b - 1, p)) % p;
    int64_t aux = powmod(a, b / 2, p);
    return (aux * aux) % p;
}

int64_t mod_inv(int64_t v, int64_t p = mod) { // v^(-1) % p
    return powmod(v, p - 2, p);
}

const int max_n = 1000000;
int64_t cat[max_n + 1];


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int64_t ans = 1;
    vector<int> cnt(max_n + 1);
    stack<int> s;
    auto remove = [&]() {
        int val = s.top();
        ans = ans * cat[cnt[val]] % mod;
        cnt[val] = 0;
        s.pop();
    };
    // next smaller algorithm
    for (int i = 0; i < n; i++) {
        while (!s.empty() && s.top() > a[i]) {
            remove();
        }
        if (cnt[a[i]]++ == 0) {
            s.push(a[i]);  // otherwise the value's inside the stack already
        }
    }
    while (!s.empty()) {
        remove();
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;

    cat[0] = cat[1] = 1;
    for (int64_t p = 2; p <= max_n; p++) {
        cat[p] = (2 * (2 * p - 1) * cat[p-1] % mod) * mod_inv(p + 1) % mod;
    }

    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

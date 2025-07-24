#include <bits/stdc++.h>
using namespace std;

bool sieve[31];

void solve() {
    int64_t n; cin >> n;
    vector<int64_t> a(n, 1);
    iota(a.begin(), a.end() - 1, 1);

    for (int64_t i = 2; i <= 30; i++) {
        if (sieve[i]) continue;

        for (int64_t j = i * i; j <= 30; j += i) sieve[j] = 1;
         
        int64_t prod = i;

        if (prod <= n - 1) {
            while (prod <= n - 1) prod *= i;
            prod /= i;
            a[n-1] *= prod;
        }
    }


    cout << n << '\n';
    for (auto& x : a) cout << x << ' ';
    cout << '\n';
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

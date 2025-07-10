#include <bits/stdc++.h>
using namespace std;

const int MAX_VALUE = int(5e8); // max value of prime detected
bitset<MAX_VALUE + 1> bs;       // bs[i] = 1: i is prime
vector<int64_t> p;              // primes list

void sieve(int64_t upper) {  // can be shown complexity is O(N log(log N))
    // sieve includes [0, upper]
    int64_t sieve_size = upper + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (int64_t i = 2; i < sieve_size; i++) if (bs[i]) {
        for (int64_t j = i * i; j < sieve_size; j += i) bs[j] = 0;
        p.push_back(i);
    }
}

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    sieve(n);
    cout << p.size() << " ";
    vector<int64_t> ans;
    for (int i = 0; i < int(p.size()) && a * i + b < int(p.size()); i++) {
        ans.push_back(p[a * i + b]);
    }
    cout << ans.size() << '\n';
    for (int64_t v: ans) cout << v << " ";
    cout << '\n';
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

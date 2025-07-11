#include <bits/stdc++.h>
using namespace std;

const int MAX_VALUE = int(1e5); // max value of prime detected
bitset<MAX_VALUE + 1> bs;       // if bs[i] = 1: i is prime
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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    iota(a.begin(), a.end(), 0);
    // could have just used sieve for each test case instead
    int pidx = int(upper_bound(p.begin(), p.end(), n) - p.begin() - 1);
    for (int i = pidx; i >= 0; i--) {
        int prime = int(p[i]);
        for (int j = 2*prime; j <= n; j += prime) {
            if (a[j] == j) {
                swap(a[j], a[prime]);
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    sieve(MAX_VALUE);
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

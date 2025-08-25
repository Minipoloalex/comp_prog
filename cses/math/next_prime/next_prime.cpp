#include <bits/stdc++.h>
using namespace std;

const int MAX_VALUE = int(1e6); // max value of prime detected
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

// requires having found primes: still is O(sqrt(n) / ln(n))
bool isprime(int64_t N) {
    vector<int64_t> factors;
    for (int i = 0; i < (int) p.size() && (p[i] * p[i]) <= N; i++) {
        if (N % p[i] == 0) return false;
    }
    return true;
}


void solve() {
    int64_t n;
    cin >> n;
    // maximal prime gaps at 1e12 is 540 (check wikipedia)
    // with sqrt(N) / log(sqrt(N)) check, we can easily brute force
    for (int64_t i = n + 1; ; i++) {
        if (isprime(i)) {
            cout << i << '\n';
            return;
        }
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    sieve(MAX_VALUE);
    while (t--) {
        solve();
    }
    return 0;
}

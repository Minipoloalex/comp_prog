#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

ll sieve_size;
bitset<10010> bs;
vll p;

vll pf; // 431 sized vector with ints corresponding to the power of the prime factor (e.g. 4 will always be 0 because it is not prime)

// another idea would be to have pf be indexed the same as p, representing the i'th primes.
// indexing when getting prime factors would be easy but getting the number of divisors might take long

void sieve(ll ub) {
    sieve_size = ub + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i < sieve_size; i++) if (bs[i]) {
        for (ll j = i * i; j < sieve_size; j += i) bs[j] = 0;
        p.push_back(i);
    }
}

void primeFactors(ll n, int to_sum) {
    for (ll i = 0; i < (ll) p.size() && p[i] * p[i] <= n; i++) {
        while (n % p[i] == 0) {
            n /= p[i];
            pf[p[i]] += to_sum;
        }
    }
    if (n != 1) pf[n] += to_sum;
}

ll numDiv() {
    ll ans = 1;
    for (ll power: pf) {
        // if (power != 0) cout << power << " ";
        if (power < 0) throw invalid_argument("power should not be negative");
        ans *= (power + 1);
    }
    // cout << endl;
    return ans;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    sieve(1e4);
    ll n, k;    // each portion max of 431
    
    while (cin >> n >> k) { // 11k, [0, 431], k <= n, C(n, k) < 2^63
        // cout << "before n: " << n << ", k: " << k << endl;
        if (k > n/2) k = n - k; // make k < n/2, so that k! is smaller
        // cout << "after n: " << n << ", k: " << k << endl;
        
        pf.assign(450, 0);
        for (ll i = n - k + 1; i <= n; i++) primeFactors(i, 1);
        for (ll i = 2; i <= k; i++) primeFactors(i, -1);
        cout << numDiv() << endl;
    }
    return 0;
}

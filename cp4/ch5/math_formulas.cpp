#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vll;

// log_b(a) = log(a) / log(b)

// log(a ^ b) = b * log(a)
// log(a * b) = log(a) + log(b)
// log(a / b) = log(a) - log(b)

inline constexpr int pct(int x) { return __builtin_popcount(x); }           // # of bits set
inline constexpr int pct(long long x) { return __builtin_popcountll(x); }   // # of bits set

int numberOfDigits(int a) {
    return (int) floor(1+log10((double)a));
}
int numberOfDigits(int a, int base) {
    return (int) floor(1+log10((double) a) /log10((double) base));
}
int mod(int a, int m) { // to ensure it's positive
    return ((a % m) + m) % m;
}
ll pow_fast(ll base, ll exp, ll mod) {
    ll result = 1;
    base = base % mod;  // avoid overflow

    while (exp > 0) {
        if ((exp & 1) == 1) { // exp is odd, multiply once result by base
            result = (result * base) % mod;
        }
        // now exp "is even", so square base
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

ll sieve_size;
const int MAX_SIZE = int(1e8) + 1;
bitset<MAX_SIZE> bs;    // 100000001
vll p;

void sieve(ll upper) {  // can be shown complexity is O(N log(log N))
    sieve_size = upper + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i < sieve_size; i++) if (bs[i]) {
        for (ll j = i * i; j < sieve_size; j += i) bs[j] = 0;
        p.push_back(i);
    }
}
vll primeFactors(ll N) {
    vll factors;
    for (int i = 0; i < (int) p.size() && (p[i] * p[i]) <= N; i++) {
        while (N % p[i] == 0) {
            N /= p[i];
            factors.push_back(p[i]);
        }
    }
    if (N != 1) factors.push_back(N);
    return factors;
}
int vp(int _p, int n) {  // Legendre's formula
    int res = 0;
    for (int pi = _p; pi <= n; pi *= _p) { // sum(i=1 -> inf, floor(n/pi))
        res += n/_p;
    }
    return res;
}
int extEuclidean(int a, int b, int &x, int &y) {
    int xx = y = 0;
    int yy = x = 1;
    while (b) {
        int q = a/b;
        int t = b; b = a % b; a = t;    // a, b = b, a % b
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;   // returns gcd(a, b)
}
int modInverse(int b, int m) {
    int x, y;
    int d = extEuclidean(b, m, x, y);
    if (d != 1) return -1;  // b * x + m * y = 1, apply (mod m) to get b * x = 1 (mod m)
    return mod(x, m);
}

/* Derangements
A  derangement is a permutation of the elements of a set in which
no element appears in its original position.
Note that inclusion exclusion with permutations and combinations would be much more complex

Formula:
derangements(n) = D(n) = (n - 1) * (D(n - 1) + D(n - 2))

!n = (n - 1) * (!(n - 1) +  !(n - 2)), n >= 2
!0 = 1, !1 = 0

def d(n):
    if n == 0: return 1
    if n == 1: return 0
    return (n - 1) * (d(n-1) + d(n-2))
*/

/*
Common sequences:
Fibonacci: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
Factorial: 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880
Derangement: 1, 0, 1, 2, 9, 44, 265, 1854, 14833
Catalan: 1, 1, 2, 5, 14, 42, 132, 429, 1430,  // Cat(n+1) = ((4n+2) / (n+2)) * Cat(n)
Bell: 1, 1, 2, 5, 15, 52, 203, 877, 4140
*/


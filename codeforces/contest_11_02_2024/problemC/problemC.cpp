#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, int> lli;
typedef vector<ll> vll;
typedef vector<lli> vlli;

ll sieve_size;
bitset<1000001> bs;
vll p;

void sieve(ll upper) {
    sieve_size = upper + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i < sieve_size; i++) if (bs[i]) {
        for (ll j = i * i; j < sieve_size; j += i) bs[j] = 0;
        p.push_back(i);
    }
}
vlli primeFactors(ll N) {
    vlli factors;
    for (int i = 0; i < (int) p.size() && (p[i] * p[i]) <= N; i++) {
        int _exp = 0;
        while (N % p[i] == 0) {
            N /= p[i];
            _exp++;
        }
        if (_exp != 0) {
            factors.emplace_back(p[i], _exp);
        }
    }
    if (N != 1) {
        if (factors.empty()) factors.emplace_back(N, 1);
        else {
            if (factors.back().first == N) {
                factors.back() = make_pair(factors.back().first, factors.back().second);
            }
            else {
                factors.emplace_back(N, 1);
            }
        }
    }
    return factors;
}
void generateDivisors(ll acc, size_t i, vlli &primeFacs, vll &divisors) {
    if (i >= primeFacs.size()) {
        divisors.push_back(acc);
        return;
    }
    auto &[_p, _exp] = primeFacs[i];
    for (int k = 0; k <= _exp; k++) {
        generateDivisors(acc * (ll) pow(_p, k), i + 1, primeFacs, divisors);
    }
}

vll divisors(ll N) {
    vlli primeFacs = primeFactors(N);
    vll divs;
    generateDivisors(1, 0, primeFacs, divs);
    return divs;
}

// vll factors(ll N)
// {
//     vll divisors;
//     divisors.push_back(1);
//     for (ll v = 2; v < N; ++v)
//     {
//         if (N % v == 0)
//         {
//             divisors.push_back(v);
//         }
//     }
//     divisors.push_back(N);
//     return divisors;
// }

int main() {
    cin.tie(NULL)->ios::sync_with_stdio(false);
    sieve(100000);
    int t;
    cin >> t;
    while (t--) {
        ll n, x;
        cin >> n >> x;
        
        // (n - x) / 2
        // (n + (x - 2)) / 2

        if ((n - x) % 2 != 0) {
            cout << 0 << '\n';
            continue;
        }
        if ((n + x - 2) % 2 != 0) {
            cout << 0 << '\n';
            continue;
        }

        ll v1 = (n - x) / 2;
        ll v2 = (n + x - 2) / 2;

        vll f1 = divisors(v1);
        vll f2 = divisors(v2);

        unordered_set<ll> ks;
        for (ll r : f1) {
            ll v = v1 / r + 1;
            if (v >= x) {
                ks.insert(v);
            }
        }
        for (ll r : f2) {
            ll v = v2 / r + 1;
            if (v >= x) {
                ks.insert(v);
            }
        }
        
        size_t result = ks.size();
        cout << result << '\n';
    }
    return 0;
}

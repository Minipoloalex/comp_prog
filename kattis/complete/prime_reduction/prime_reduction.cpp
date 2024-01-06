#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

ll sieve_size;
bitset<100000001> bs;
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

ll sum(const vll &pf) {
    ll res = 0;
    for (ll val: pf) res += val;
    return res;
}

int main() {
    // 4 not included in the sequence
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    sieve(1e7);
    ll n;
    while (cin >> n) {
        if (n == 4) break;
        int ct = 0;
        while (true) {
            vll pf = primeFactors(n);
            ct++;
            if (pf.size() == 1) {
                cout << n << " " << ct << endl;
                break;
            }
            else n = sum(pf);
        }
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
ll sieve_size;
bitset<10000010> bs;
vll p;

void sieve(ll ub) {
    sieve_size = ub + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i < sieve_size; i++) if (bs[i]) {
        for (ll j = i * i; j < sieve_size; j += i) bs[j] = 0;
        p.push_back(i);
    }
}

ll eulerPhi(ll n) {
    ll ans = n;
    for (ll i = 0; i < (ll) p.size() && p[i] * p[i] <= n; i++) {
        if (n % p[i] == 0) ans -= ans/p[i]; 
        while (n % p[i] == 0) n /= p[i];
    }
    if (n != 1) ans -= ans/n;
    return ans;
}

int main() {
    sieve(1e6);
    int n;
    while (cin >> n) {
        if (n == 0) break;
        ll res = eulerPhi(n);
        cout << res << endl;
    }
    return 0;
}

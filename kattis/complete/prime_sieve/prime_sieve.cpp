#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll sieve_size;
bitset<100000001> bs;
ll n_primes;

void sieve(ll upper) {
    sieve_size = upper + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i < sieve_size; i++) if (bs[i]) {
        for (ll j = i * i; j < sieve_size; j += i) bs[j] = 0;
        n_primes++;
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    n_primes = 0;
    sieve(n);
    cout << n_primes << endl;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        if (bs[x]) cout << 1 << endl;
        else cout << 0 << endl;
    }    
    return 0;
}

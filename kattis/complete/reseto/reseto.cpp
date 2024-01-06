#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

bitset<100010> bs;

ll sieve(ll ub, ll k) {
    bs.set();
    bs[0] = bs[1] = 0;
    ll _count = 0;
    for (int i = 2; i < ub; i++) if (bs[i]) {
        for (int j = i; j < ub; j += i) {
            // do not care about resulting primes
            if (bs[j] == 1) {
                // cout << j << " ";
                bs[j] = 0;
                _count++;
                if (_count == k) return j;
            }
        }
    }
    while(1);
    return -1;
}

int main() {
    int n, k;
    cin >> n >> k;
    ll res = sieve(n + 1, k);
    // cout << endl;
    cout << res << endl;
    return 0;
}

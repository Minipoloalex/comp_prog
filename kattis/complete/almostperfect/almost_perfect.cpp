#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;

int sieve_size;
bitset<100010> bs;
vi p;

void sieve(int ub) {
    sieve_size = ub + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (int i = 2; i < sieve_size; i++) if (bs[i]) {
        for (ll j = i * i; j < sieve_size; j += i) bs[j] = 0;
        p.push_back(i);
    }
}

ll sumDiv(int n) {
    ll ans = 1;
    for (int i = 0; i < (int) p.size() && p[i] * p[i] <= n; i++) {
        ll multiplier = p[i], total = 1;    // total = p[i]^0
        while (n % p[i] == 0) {
            n /= p[i];
            total += multiplier;    // sum to total a^i
            multiplier *= p[i];
        }
        ans *= total;   // total will be sum(a^i), Vi s.t. a^i | n (divides)
    }
    if (n != 1) ans *= 1 + n;
    return ans;
}

int main() {
    // perfect -> sum(divisors) = n
    // almost perfect -> n - 2 <= sum(divisors) <= n + 2   
    sieve(31623);   // was resulting in seg fault after 46337 (don't know why)
    int n;
    while (cin >> n) {  // [2, 1e9]
        ll sumPD = sumDiv(n) - n;
        if (sumPD == n) cout << n << " perfect" << endl;
        else if (abs(sumPD - n) <= 2) cout << n << " almost perfect" << endl;
        else cout << n << " not perfect" << endl;
    }
    return 0;
}

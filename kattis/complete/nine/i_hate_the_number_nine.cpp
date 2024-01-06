#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

ull pow_fast(ull base, ull exp, ull mod) {
    ull result = 1;
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

int main() {
    int T;
    cin >> T;   // [1, 20]
    while (T--) {
        ull d;
        cin >> d;   // [1, 1e18]
        // positive numbers with d digits that do not have a nine
        ull mod = 1e9 + 7;
        ull res = (8 * (ull) pow_fast(9, d - 1, mod)) % mod;

        cout << res << endl;
    }
    return 0;
}

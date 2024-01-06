#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

ull mod(ll a, ll m) {
    return ((a % m) + m) % m;
}
ull extEuclidean(ll a, ll b, ll &x, ll &y) {
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {
        ll q = a/b;
        ll t = b; b = a % b; a = t;    // a, b = b, a % b
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;   // returns gcd(a, b)
}
ll modInverse(ll b, ll m) {
    ll x, y;
    ull d = extEuclidean(b, m, x, y);
    if (d != 1) return -1;  // b * x + m * y = 1, apply (mod m) to get b * x = 1 (mod m)
    return mod(x, m);
}
ll numberOfDigits(ll a) {
    return (ll) floor(1+log10((double)a));
}
bool overflowed(ll res, ll n1, ll n2) {
    return numberOfDigits(res) < numberOfDigits(n1) * numberOfDigits(n2);
    // return res < n1 || res < n2;
}


void multiply_mod(ll a, ll &b, ull m, ll &current_b, ull &res) {
    /*
    if (b == 0 || current_b == 0) return;
    if (overflowed(a * current_b, a, current_b)) {
        cout << "Overflow: " << a << ", " << b << ", " << current_b << ", " << a * current_b <<endl;
        current_b /= 2;
        multiply_mod(a, b, m, current_b, res);
        return;
    }
    cout << "No overflow: " << a << ", " << b << ", " << current_b << ", " << a * current_b << endl;
    res = mod(res + mod(a * current_b, m), m);
    b -= current_b;
    current_b = b;
    multiply_mod(a, b, m, current_b, res);
    // Does not work because we're multiplying a per b and summing to res, not multiplying res per b.
    */
    /*
    Does not work because 32 bits numbers multiplied result in 64 bits and << 32 will never work properly
    // if (split_by <= 8) return mod(a * b, m);
    // ull a_ms = a >> split_by;
    // ull a_ls = a & (ull) (BIT(split_by)-1); // 0xFFF...
    // ull b_ms = b >> split_by;
    // ull b_ls = b & (ull) (BIT(split_by)-1);

    // cout << a_ms << " " << a_ls << " " << b_ms << " " << b_ls << ", m: " << m << endl;
    // // e.g. (a_ms*2^32 + a_ls) * (b_ms*2^32 + b_ls)
    // ull res = 0;
    
    // res = multiply_mod(a, b, m, split_by/2);
    // res = mod(a_ms * b_ms, m);

    // // have to apply this function recursively because e.g. (bits): 30 * 30 = 60, 60 << 32 > 64.
    // res = mod(res << split_by, m);
    // res = mod(res << split_by, m);

    // return a;
    */
}

int main() {
    ull n, t;
    while (cin >> n >> t) {
        if (n == 0 && t == 0) break;
        for (ull i = 0; i < t; i++) {
            ll a, b;
            char c;
            cin >> a >> c >> b;
            ll mInv;
            ull res = 0;
            ll curr_b = b;
            switch (c) {
                case '/':
                    if (b == 0) cout << -1 << endl;
                    else {
                        mInv = modInverse(b, n);
                        if (mInv == -1) cout << -1 << endl;
                        else cout << mod(a * modInverse(b, n), n) << endl;
                    }
                    break;
                case '*':
                    multiply_mod(a, b, n, curr_b, res);
                    cout << res << endl;
                    // cout << mod(a * b, n) << endl;
                    break;
                case '+':
                    cout << mod(a + b, n) << endl;
                    break;    
                case '-':
                    cout << mod(a - b, n) << endl;
                    break;
            }
        }
    }
    return 0;
}

// TODO: test big numbers and overflow

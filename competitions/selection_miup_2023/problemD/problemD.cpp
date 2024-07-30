#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;


int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    ull n;
    cin >> n;
    ull evens = 0;
    ull odds = 1;   // the number 1
    ull mod = 1e6 + 7;
    for (ull i = 0; i < n - 1; i++) {
        ull temp = evens;
        evens = (odds + evens) % mod;
        odds = temp % mod;
    }
    cout << ((odds + evens) % mod) << endl;
    return 0;
}

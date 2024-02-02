#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX_N = 1e5 + 10;
const int md = 1e9 + 7;

vector<ll> fib;

ll fibdp(int n) {
    if (fib[n] != -1) {
        return fib[n];
    }    
    return (fib[n] = (fibdp(n - 1) + fibdp(n - 2)) % md);
}

int main() {
    int T;
    cin >> T;
    fib.assign(MAX_N, -1);
    fib[0] = 1;
    fib[1] = 1;
    while (T--) {
        int n;
        cin >> n;
        cout << fibdp(n + 1) << '\n';
    }
    return 0;
}

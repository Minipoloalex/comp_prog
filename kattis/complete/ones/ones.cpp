#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int main() {    // also UVa 10127
    // no trailing zeros
    // x * n = 1111...
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    ull n;
    while (cin >> n) {  // [1, 1e5]
        ull digits = 1;
        ull r = 1 % n;
        while (r != 0) {  // loop through numbers like 1, 11, 111, 1111, 11111, ...
            r = ((r * 10) % n + 1) % n;
            digits++;
        }
        cout << digits << endl;
    }
    return 0;
}

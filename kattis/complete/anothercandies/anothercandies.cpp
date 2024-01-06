#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int main() {
    int t; cin >> t;
    int n;
    while (t--) {   // [1, 100]
        cin >> n;   // [1, 20k]
        ull total = 0;
        for (int i = 0; i < n; i++) {
            ull ci; cin >> ci;
            total = (total + ci % n) % n;
        }
        cout << (total == 0 ? "YES" : "NO") << endl;
    }
    return 0;
}

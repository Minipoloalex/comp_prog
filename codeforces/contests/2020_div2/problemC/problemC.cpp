#include <bits/stdc++.h>
using namespace std;

#define BIT(n) (1LL << (n))

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int64_t b, c, d;
        cin >> b >> c >> d;
        int64_t a = 0;
        bool possible = true;
        for (int i = 0; i < 63 && possible; i++) {
            int64_t bit_i = BIT(i);
            // I built the truth table to help build these cases
            int64_t bit_b = (b & bit_i);
            int64_t bit_c = (c & bit_i);
            int64_t bit_d = (d & bit_i);
            if (bit_b == 0 && bit_c == 0) a |= bit_d;
            else if (bit_b == 0 && bit_c != 0) {
                if (bit_d != 0) possible = false;
            }
            else if (bit_b != 0 && bit_c == 0) {
                if (bit_d == 0) possible = false;
                // bit_a can be 0 or 1
            }
            else {
                // assert(bit_b != 0 && bit_c != 0);
                if (bit_d == 0) a |= bit_i;
                // otherwise the bit is 0
            }
        }
        if (!possible) cout << "-1\n";
        else cout << a << '\n';
    }
}

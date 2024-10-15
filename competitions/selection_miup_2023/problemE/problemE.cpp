#include <bits/stdc++.h>
using namespace std;

#define BIT(n) (1LL << (n))

int main() {
    int Q;
    cin >> Q;
    /*
    000...*.*.*
    100...*.*.*
    -> 0 (ans = 32)
    */
    vector<int> mn(4, INT_MAX), mx(4, INT_MIN);
    char _;
    while (Q--) {
        int values[4];
        for (int i = 0; i < 4; i++) {
            cin >> values[i];
            if (i != 3) cin >> _;

            mn[i] = min(mn[i], values[i]);
            mx[i] = max(mx[i], values[i]);
        }
    }

    int64_t mnval = (mn[0] << 24) | (mn[1] << 16) | (mn[2] << 8) | mn[3];
    int64_t mxval = (mx[0] << 24) | (mx[1] << 16) | (mx[2] << 8) | mx[3];
    int index = 31;
    while (index >= 0 && (mnval & BIT(index)) == (mxval & BIT(index))) {
        index--;
    }
    // result = 4
    // 24 + 0000....
    //      0001....
    // cout << index << endl;
    int ans = (32 - (index + 1));
    if (ans == 0) {
        ans = 32;
    }
    cout << ans << '\n';
    return 0;
}

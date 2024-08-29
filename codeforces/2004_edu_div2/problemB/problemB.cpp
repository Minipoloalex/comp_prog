#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int l, r, L, R;
        cin >> l >> r >> L >> R;

        bool a = (L < l && r < R);  // totally inside L l r R
        bool b = (l < L && R < r);  // totally inside l L R r

        int value;
        if (l == L && r == R) { // equal
            value = r - l;
        }
        else if (r < L || R < l) {   // totally outside (l r L R) || (L R l r)
            value = 1;
        }
        else if (a) {
            value = r - l + 2;
        }
        else if (b) {
            value = R - L + 2;
        }
        else {  // partially inside: l L r R or L l R r
            if (L == r || l == R) {
                value = 2;
            }
            else {
                if (l == L || r == R) {
                    value = min(r, R) - max(l, L) + 1;
                }
                else {
                    value = min(r, R) - max(l, L) + 2;
                }
            }
        }
        cout << value << '\n';
    }
    return 0;
}

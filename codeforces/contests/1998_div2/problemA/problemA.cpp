#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int xc, yc, k;
        cin >> xc >> yc >> k;
        int cnt = 1;
        for (int i = 0; i < k / 2; i++) {
            cout << xc + cnt << " " << yc << '\n';
            cout << xc - cnt << " " << yc << '\n';
            cnt++;
        }
        if (k & 1) {    // odd
            cout << xc << " " << yc << '\n';
        }
    }
    return 0;
}

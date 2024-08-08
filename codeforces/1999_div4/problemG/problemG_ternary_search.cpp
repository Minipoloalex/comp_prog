#include <bits/stdc++.h>
using namespace std;

int correct(int a, int b) {
    cout << "? " << a << " " << b << '\n';
    cout << flush;
    int area;
    cin >> area;
    if (a * b == area) return 0;
    if (a * (b + 1) == area) return 1;
    if ((a + 1) * (b + 1) == area) return 2;

    throw exception();
    return -1;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int mn = 1, mx = 1000;
        int ans;
        while (mn <= mx) {
            int t1 = mn + (mx - mn) / 3;
            int t2 = mn + (2 * (mx - mn)) / 3;
            int result = correct(t1, t2);
            if (result == 0) {  // both correct (wrong after t2)
                mn = t2 + 1;
            }
            else if (result == 1) { // in the middle (t2 wrong)
                mn = t1 + 1;
                mx = t2 - 1;
                ans = t2;
            }
            else {  // both t1, t2 wrong [mn, t1, t2, mx]
                ans = t1;
                mx = t1 - 1;
            }
        }
        cout << "! " << ans << '\n';
    }    
    return 0;
}

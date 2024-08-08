#include <bits/stdc++.h>
using namespace std;

bool correct(int value) {
    cout << "? " << value << " " << value << '\n';
    cout << flush;
    int area;
    cin >> area;
    return area == value * value;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int mn = 1, mx = 1000;
        int ans;
        while (mn <= mx) {
            int middle = (mn + mx) / 2;
            if (correct(middle)) {
                mn = middle + 1;
            }
            else {
                ans = middle;
                mx = middle - 1;
            }
        }
        cout << "! " << ans << '\n';
    }    
    return 0;
}

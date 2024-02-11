#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        if (a % 2 == 1 && b % 2 == 1) {
            cout << "NO" << '\n';
        }
        else if (a % 2 == 0 && b % 2 == 0) {
            cout << "YES" << '\n';
        }
        else {
            int even = a % 2 == 0 ? a : b;
            int odd = b % 2 == 1 ? b : a;
            int cut = even / 2;
            if (cut != odd) {
                cout << "YES" << '\n';
            }
            else {
                cout << "NO" << '\n';
            }
        }
    }    
    return 0;
}

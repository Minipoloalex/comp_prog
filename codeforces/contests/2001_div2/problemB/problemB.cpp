#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n % 2 == 0) {
            cout << "-1\n";
        }
        else {
            int nr_carriages = n / 2;  // e.g. 5 / 2 = 2
            int nn = n;
            for (int i = 0; i < nr_carriages; i++, nn--) {
                cout << nn << " ";
            }
            for (int i = 1; i <= n - nr_carriages; i++) {
                cout << i << " ";
            }
            cout << '\n';
        }
    }
    return 0;
}

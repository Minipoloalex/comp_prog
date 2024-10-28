#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    string nr5 = "36366";
    string nr2 = "66";
    while (t--) {
        int n;
        cin >> n;
        // 66 | n -> 66 | 33n
        if (n == 1 || n == 3) {
            cout << "-1\n";
        }
        else {
            if ((n & 1) == 1) {
                for (int i = 0; i < n - 5; i++) {
                    cout << "3";
                }
                cout << nr5 << '\n';
            }
            else {
                for (int i = 0; i < n - 2; i++) {
                    cout << "3";
                }
                cout << nr2 << '\n';
            }
        }
    }
    return 0;
}

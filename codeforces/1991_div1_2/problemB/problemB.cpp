#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> b(n - 1);
        for (int i = 0; i < n - 1; i++) {
            cin >> b[i];
        }
        vector<int> a(n);
        a[0] = b[0];
        for (int i = 1; i < n - 1; i++) {
            a[i] = b[i - 1] | b[i];
        }
        a[n - 1] = b[n - 2];

        bool solution = true;
        for (int i = 0; i < n - 1 && solution; i++) {
            if (b[i] != (a[i] & a[i + 1])) solution = false;
        }
        if (solution) {
            for (int v: a) {
                cout << v << " ";
            }
            cout << '\n';
        }
        else cout << "-1\n";
    }
    return 0;
}

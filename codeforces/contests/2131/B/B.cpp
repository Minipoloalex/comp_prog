#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            cout << "-1 ";
        }
        else {
            if (i == n - 1) {
                cout << "2 ";
            }
            else {
                cout << "3 ";
            }
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

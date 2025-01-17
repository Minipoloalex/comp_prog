#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n == 6) {
        cout << "1 1 2 3 1 2\n";
        return;
    }
    cout << "1 2 ";
    for (int i = 3; i <= n - 2; i++) {
        cout << i << " ";
    }
    cout << "1 2\n";
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

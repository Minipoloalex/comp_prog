#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> b(n - 2);
    bool yes = true;
    for (int i = 0; i < n - 2; i++) {
        cin >> b[i];
        if (i >= 2 && b[i - 2] == 1 && b[i - 1] == 0 && b[i] == 1) {
            yes = false;
        }
    }
    cout << (yes ? "YES" : "NO") << '\n';
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

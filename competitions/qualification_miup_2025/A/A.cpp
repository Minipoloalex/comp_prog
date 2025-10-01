#include <bits/stdc++.h>
using namespace std;

void solve() {
    string a, b, c;
    cin >> a >> b >> c;
    int n = int(c.size());
    for (int i = 0; i < n; i++) {
        if (c[i] == 'D') {
            a.push_back(b[i]);
        }
        else {
            a.insert(a.begin(), b[i]);
        }
    }
    cout << a << '\n';
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) { 
        solve();
    }
    return 0;
}

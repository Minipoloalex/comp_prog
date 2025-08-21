#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    string a, b, c;
    cin >> n >> a >> m >> b >> c;
    // V: begin
    // D: end
    for (int i = 0; i < m; i++) {
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
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

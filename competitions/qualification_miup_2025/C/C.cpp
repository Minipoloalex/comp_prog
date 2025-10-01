#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());
    vector<int> x(s.size());
    for (int i = 0; i < n; i++) {
        int v;
        if (s[i] == 'I') v = 1;
        else if (s[i] == 'V') v = 5;
        else if (s[i] == 'X') {
            v = 10;
        }
        else if (s[i] == 'L') {
            v = 50;
        }
        else if (s[i] == 'C') {
            v = 100;
        }
        else if (s[i] == 'D') {
            v = 500;
        }
        else {
            v = 1000;
        }
        x[i] = v;
        // cout << v << " ";
    }
    // cout << endl;
    vector<int> sufmax(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        sufmax[i] = max(sufmax[i + 1], x[i]);
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        if (sufmax[i] == x[i]) {
            ans += x[i];
        }
        else {
            ans -= x[i];
        }
    }
    cout << ans << '\n';
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

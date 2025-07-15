#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    
    int cur = 1, pos = n-1;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') {
            pos = min(pos, i);
            a[i] = cur++;
        }
        if (i > 0 && s[i-1] == s[i] && s[i] == 'B') {
            cout << -1 << '\n';
            return;
        }
    }

    if (cur == 1) {
        cout << -1 << '\n';
        return;
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') a[i] = cur++;
    }

    reverse(a.begin(), a.begin() + pos);
    
    for (int i = 0; i < n; i++)
        cout << a[i] << " \n"[i == n-1];
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

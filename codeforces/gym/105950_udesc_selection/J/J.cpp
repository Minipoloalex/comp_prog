#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int cnto = 0, cntdot = 0;
    int i;
    for (i = 1; i < n - 1; i++) {
        if (s[i] == 'o') {
            cnto++;
        }
        else if (s[i] == '.' && k == 0) break;
        else if (s[i] == '.') {
            cntdot++;
            k--;
        }
    }
    cout << string(cntdot, '.');
    cout << '#';
    cout << string(cnto, 'o');
    for (int j = i; j < n - 1; j++) {
        cout << s[j];
    }
    cout << "#\n";
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

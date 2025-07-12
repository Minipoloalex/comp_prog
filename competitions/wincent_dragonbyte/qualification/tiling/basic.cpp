#include <bits/stdc++.h>
using namespace std;

string alph = "abcdefghijklmnopqrstuvwxyz";
// char get(char a, char b) {
//     if ((a == 'a' && b == 'b') || (a == 'b' && b == 'a')) return 'c';
//     if (a == 'a' || b == 'a') return 'b';
//     return 'a';
// }
void solve() {
    int n;
    cin >> n;
    vector<string> g(n, string(n, ' '));
    bool ans;
    if (n % 2 == 0) {
        ans = true;
        int idx = 0;
        for (int i = 0; i < n; i += 2) {
            for (int j = 0; j < n; j += 2) {
                g[i][j] = alph[idx % 26];   // works for this (does not work for n = 52*k)
                g[i+1][j] = alph[idx % 26];
                g[i][j+1] = alph[idx % 26];
                g[i+1][j+1] = alph[idx % 26];
                idx++;
            }
        }
    }
    else {
        if (n <= 5) ans = false;
        // ...
    }

    if (ans) {
        cout << "YES\n";
        for (string s: g) cout << s << '\n';
    }
    else {
        cout << "NO\n";
    }
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

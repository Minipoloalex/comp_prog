#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        string s, t;
        cin >> s >> t;
        int n = (int) s.size();
        int m = (int) t.size();
        int i, j;
        for (i = 0, j = 0; i < n && j < m; i++) {
            if (s[i] == t[j]) j++;
            else if (s[i] == '?') {
                s[i] = t[j];
                j++;
            }
        }
        if (j == m) {
            cout << "YES\n";
            if (i < n) {
                for (; i < n; i++) if (s[i] == '?') s[i] = 'a';
            }
            cout << s << '\n';
        }
        else cout << "NO\n";
    }
    return 0;
}

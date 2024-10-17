#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    while (q--) {
        string s, t;
        cin >> s >> t;
        int n = int(s.size());
        int m = int(t.size());
        int i = 0;
        for (; i < n && i < m && s[i] == t[i]; i++);

        int ans = 0;
        if (i > 0) {
            ans++;
        }
        ans += i + (n - i) + (m - i);
        cout << ans << '\n';
    }
    return 0;
}

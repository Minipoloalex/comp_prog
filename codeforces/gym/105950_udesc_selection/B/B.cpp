#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    string cp = s;
    sort(cp.begin(), cp.end());

    for (int i = 0; i < n; i++) {
        if (s[i] != cp[i]) {
            for (int j = n - 1; j >= 0; j--) {
                if (s[j] == cp[i]) {
                    swap(s[i], s[j]);
                    break;
                }
            }
            break;
        }
    }

    cout << s << endl;
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

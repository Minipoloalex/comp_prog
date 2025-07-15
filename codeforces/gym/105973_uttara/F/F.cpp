#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    if (n >= 5) {
        cout << "NO\n";
    } else {
        bool can = true;

        for (int i = 2; i <= 4; i++) {
            for (int j = 0; j < n - i + 1; j++) {
                string sub = s.substr(j, i);
                int num = atoi(sub.c_str());
                if (num % i != 0) {
                    can = false;
                }
            }
        }

        cout << (can ? "YES" : "NO") << '\n';
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

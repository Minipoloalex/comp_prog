#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int cnt = 0;
    int cnt3 = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s.find("xxx") != string::npos) {
            cnt3++;
        }
        else if (s.find("xx") != string::npos) {
            cnt++;
        }
    }
    bool ans = true;
    if (cnt % 2 == 0 && cnt3 % 2 == 0) ans = false;
    cout << (ans ? "Monocarp" : "Polycarp") << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

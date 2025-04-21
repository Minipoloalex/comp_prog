#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());
    bool niseven = n % 2 == 0;
    vector<int> cnt(26, 0);
    for (char c: s) {
        int cidx = c - 'A';
        cnt[cidx]++;
    }
    bool good = true;
    string ans(n, '\0');
    int cur = 0;
    for (int i = 0; i < 26; i++) {
        char c = char('A' + i);
        while (cnt[i] > 1) {
            ans[n - 1 - cur] = c;
            ans[cur] = c;
            cur++;
            cnt[i] -= 2;
        }
        if (cnt[i] == 1) {
            if (niseven || ans[n / 2] != '\0') {
                good = false;
                break;
            }
            else {
                ans[n / 2] = c;
            }
        }
    }
    if (good) {
        cout << ans << '\n';
    }
    else {
        cout << "NO SOLUTION\n";
    }
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

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        vector<int> cnt(4, 0);
        for (int i = 0; i < 4 * n; i++) {
            char c = s[i];
            if (c != '?') {
                cnt[c - 'A']++;
            }
        }
        int ans = 0;
        for (int i = 0; i < 4; i++) {
            if (cnt[i] > n) cnt[i] = n;
            ans += cnt[i];
        }
        cout << ans << '\n';
    }
    return 0;
}

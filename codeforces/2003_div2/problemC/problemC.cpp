#include <bits/stdc++.h>
using namespace std;


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;

        int a[26];
        memset(a, 0, sizeof(a));
        for (char c: s) a[c - 'a']++;

        string ans;
        for (int i = 0; i < n; i++) {
            int max_freq = -1, ch = -1;
            for (int j = 0; j < 26; j++) {
                if (a[j] > max_freq) {
                    max_freq = a[j];
                    ch = j;
                }
            }
            assert(ch != -1);
            a[ch]--;
            ans += char(ch + 'a');
        }
        cout << ans << '\n';
    }
    return 0;
}

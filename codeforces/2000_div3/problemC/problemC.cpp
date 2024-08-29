#include <bits/stdc++.h>
using namespace std;

int ch_to_int[26];

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cout.tie(0);

    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n;
        cin >> n;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        int m;
        cin >> m;

        while (m--) {
            string s;
            cin >> s;

            if ((int) s.size() != n) {
                cout << "NO\n";
            }
            else {
                set<int> nrs;
                for (int i = 0; i < 26; i++) {
                    ch_to_int[i] = INT_MAX;
                }

                bool yes = true;
                for (int i = 0; i < n && yes; i++) {
                    char c = s[i];
                    int idx = c - 'a';

                    bool already_seen_character = ch_to_int[idx] != INT_MAX;
                    if (already_seen_character && ch_to_int[idx] != a[i]) {
                        yes = false;
                    }
                    else if (!already_seen_character && nrs.find(a[i]) != nrs.end()) {
                        yes = false;
                    }
                    ch_to_int[idx] = a[i];
                    nrs.insert(a[i]);
                }
                if (yes) cout << "YES\n";
                else cout << "NO\n";
            }
        }
    }
    return 0;
}

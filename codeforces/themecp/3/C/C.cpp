#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string t;
    cin >> t;
    vector<int> saved(26, -1), mp(26, -1);
    int ts = int(t.size());
    string ans;
    int cnt = 0;
    for (int i = 0; i < ts; i++) {
        int c = t[i] - 'a';
        if (saved[c] == -1) {
            int selected = INT_MAX;
            if (cnt == 25) {
                selected = int(find(mp.begin(), mp.end(), -1) - mp.begin());
            }
            else {
                int cur = c;
                vector<bool> possible(26, 1);
                while (cur != -1) {
                    possible[cur] = 0;
                    cur = mp[cur];
                }
                for (int j = 0; j < 26; j++) {
                    if (possible[j] && mp[j] == -1) {
                        selected = j;
                        break;
                    }
                }
            }
            assert(selected != INT_MAX);
            cnt++;
            mp[selected] = c;
            saved[c] = selected;
        }
        ans += char(saved[c] + 'a');
    }
    cout << ans << '\n';
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

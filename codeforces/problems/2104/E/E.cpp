#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vvi nxt(n + 1, vi(k, -1));
    vi cost(n + 1, INT_MAX);    // don't need to worry about cost[0]
    vector<int> cur(k, -1);
    for (int i = n; i >= 1; i--) {
        for (int ch = 0; ch < k; ch++) {
            char c = char('a' + ch);
            nxt[i][ch] = cur[ch];
            int cur_cost = nxt[i][ch] == -1 ? 1 : 1 + cost[nxt[i][ch]];
            if (s[i - 1] == c) {
                cur[ch] = i;
            }
            cost[i] = min(cost[i], cur_cost);            
        }
    }
    for (int i = 0; i < k; i++) {
        nxt[0][i] = cur[i];
    }
    // for (int i = 0; i <= n; i++) {
    //     for (int c = 0; c < k; c++) {
    //         cout << nxt[i][c] << " ";
    //     }
    //     cout << endl;
    // }
    // for (int i = 0; i <= n; i++) {
    //     cout << cost[i] << " ";
    // }
    // cout << endl;
    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        int m = int(t.size());
        int i = 0;
        bool is = true;
        for (int j = 0; j < m; j++) {
            int ch = t[j] - 'a';
            if (nxt[i][ch] == -1) {
                is = false;
                break;
            }
            i = nxt[i][ch];
        }
        // cout << i << " ";
        int ans;
        if (!is) {
            ans = 0;
        }
        else {
            ans = cost[i];
        }
        cout << ans << '\n';
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

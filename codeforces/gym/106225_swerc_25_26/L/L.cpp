#include <bits/stdc++.h>
using namespace std;

int g[26];

int get_ans() {
    vector<int> ans(26,-1);
    function<int(int)> go = [&](int u) {
        if (u == -1) return 0;
        if (ans[u] != -1) return ans[u];
        return ans[u] = 1 + go(g[u]);
    };
    int ret = 0;
    for (int i = 0; i < 26; i++) ret = max(ret, go(i));
    return ret;
}

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<array<int,26>> pref(n+1,array<int,26>{});
    for (int i = 0; i < n; i++) {
        pref[i+1] = pref[i];
        pref[i+1][s[i]-'a']++;
    }
    vector<vector<int>> occ(26);
    for (int i = 0; i < n; i++) {
        occ[s[i]-'a'].push_back(i);
    }

    array<int,26> empty; for (int i = 0; i < 26; i++) empty[i]=n;

    vector<array<int,26>> nxt(n+1,empty);
    for (int i = n-1; i >= 0; i--) {
        nxt[i] = nxt[i+1];
        nxt[i][s[i]-'a'] = i;
    }
    vector<int> sw(n+1,n);
    for (int i = n-1; i >= 0; i--) {
        int c = s[i]-'a';
        int nx = nxt[i+1][c];
        if (nx+1 < n && s[nx+1] != s[i+1]) {
            sw[i] = nx;
        }
        else {
            sw[i] = sw[nx];
        }
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        array<int,26> freq{};
        int mx = 0;
        for (int i = 0; i < 26; i++) {
            freq[i] = pref[r][i]-pref[l-1][i];
            mx = max(mx, freq[i]);
        }
        vector<int> most;
        for (int i = 0; i < 26; i++) {
            if (freq[i] == mx) most.push_back(i);
        }

        for (int i = 0; i < 26; i++) g[i] = -1;
        for (int c: most) {
            int lst = *prev(upper_bound(occ[c].begin(), occ[c].end(), r-1));
            int idx = nxt[l-1][c];
            if (lst + 1 < r && sw[idx] >= r && s[lst+1] == s[idx+1]) {
                g[c] = s[idx+1]-'a';
            }
        }
        int ans = get_ans();
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

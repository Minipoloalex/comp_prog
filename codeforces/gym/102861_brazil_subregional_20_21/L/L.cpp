#include <bits/stdc++.h>
using namespace std;

int ch(char c) {
    return c - 'A';
}

void reset(array<int,26> &cnt) {
    for (int i = 0; i < 26; i++) cnt[i] = 0;
}

void solve() {
    int L, C;
    cin >> L >> C;
    vector<string> g(L);
    for (auto &s: g) cin >> s;
    vector<vector<int>> colors(L, vector<int>(C));
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        array<int,26> cnt{};
        for (char c: s) {
            cnt[ch(c)]++;
        }
        int sz = int(s.size());
        for (int r = 0; r < L; r++) {
            for (int c = 0; c < C; c++) {
                array<int,26> actual_cnt{};
                for (int x = 0; x < sz && c + x < C; x++) {  // to the right
                    actual_cnt[ch(g[r][c+x])]++;
                }
                if (cnt == actual_cnt) {
                    for (int x = 0; x < sz && c + x < C; x++) {  // to the right
                        colors[r][c+x] |= (1 << i);
                    }
                }
                reset(actual_cnt);
                for (int x = 0; x < sz && r + x < L; x++) {  // to the bottom
                    actual_cnt[ch(g[r+x][c])]++;
                }
                if (cnt == actual_cnt) {
                    for (int x = 0; x < sz && r + x < L; x++) {  // to the bottom
                        colors[r+x][c] |= (1 << i);
                    }
                }
                reset(actual_cnt);
                for (int x = 0; x < sz && r + x < L && c + x < C; x++) {  // to the bottom-right
                    actual_cnt[ch(g[r+x][c+x])]++;
                }
                if (cnt == actual_cnt) {
                    for (int x = 0; x < sz && r + x < L && c + x < C; x++) {  // to the bottom-right
                        colors[r+x][c+x] |= (1 << i);
                    }
                }
                reset(actual_cnt);
                for (int x = 0; x < sz && r + x < L && c - x >= 0; x++) {  // to the bottom-left
                    actual_cnt[ch(g[r+x][c-x])]++;
                }
                if (cnt == actual_cnt) {
                    for (int x = 0; x < sz && r + x < L && c - x >= 0; x++) {  // to the bottom-left
                        colors[r+x][c-x] |= (1 << i);
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int r = 0; r < L; r++) {
        for (int c = 0; c < C; c++) {
            if (colors[r][c] > 0 && __builtin_popcount(colors[r][c]) > 1) {
                ans++;
            }
        }
    }
    cout << ans << '\n';
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> cards(n, vector<int>(m));
    bool possible = true;
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> cards[i][j];
        }
        sort(cards[i].begin(), cards[i].end());
        int mn = cards[i][0];
        if (mn >= n) {
            possible = false;
        }
        else {
            ans[mn] = i;
        }
        for (int j = 1; j < m; j++) {
            if (cards[i][j] - cards[i][j - 1] != n) {
                possible = false;
            }
        }
    }
    if (!possible) cout << "-1\n";
    else {
        for (int a: ans) cout << a + 1 << " ";
        cout << '\n';
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

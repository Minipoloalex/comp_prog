#include <bits/stdc++.h>
using namespace std;

int prefA[200010][26];
int prefB[200010][26];

int total_different(int l, int r) {
    int total = 0;
    for (int i = 0; i < 26; i++) {
        int cta = prefA[r][i] - prefA[l - 1][i];
        int ctb = prefB[r][i] - prefB[l - 1][i];
        total += abs(cta - ctb);
    }
    // cout << l << " " << r << " " << total << endl;
    return total / 2;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        memset(prefA, 0, n);
        memset(prefB, 0, n);

        string a, b;
        cin >> a >> b;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 26; j++) {
                prefA[i][j] = prefA[i - 1][j];
            }
            char c = a[i - 1];
            prefA[i][c - 'a']++;
            // cout << c << " " << prefA[i][c - 'a'] << '\n';
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 26; j++) {
                prefB[i][j] = prefB[i - 1][j];
            }
            char c = b[i - 1];
            prefB[i][c - 'a']++;
            // cout << c << " " << prefB[i][c - 'a'] << '\n';
        }

        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            int ans = total_different(l, r);
            cout << ans << '\n';
        }
    }
    return 0;
}

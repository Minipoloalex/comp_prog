#include <bits/stdc++.h>
using namespace std;

string s[2];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cin >> s[0] >> s[1];
        int ans = 0;
        for (int i = 1; i < n - 1; i++) {
            for (int j = 0; j < 2; j++) {
                int other_row = 1 - j;
                if (s[other_row][i - 1] == 'x' && s[other_row][i] == '.' && s[other_row][i + 1] == 'x'
                     && s[j][i - 1] == '.' && s[j][i + 1] == '.') ans++;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

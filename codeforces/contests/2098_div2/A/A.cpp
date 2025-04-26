#include <bits/stdc++.h>
using namespace std;

void solve() {
    string n;
    cin >> n;
    vector<int> cnt(10, 0);
    for (int i = 0; i < 10; i++) {
        int c = n[i] - '0';
        cnt[c]++;
    }

    string ans;
    for (int i = 9; i >= 0; i--) {
        for (int j = i; j < 10; j++) {
            if (cnt[j] > 0) {
                ans += char('0' + j);
                cnt[j]--;
                break;
            }
        }
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

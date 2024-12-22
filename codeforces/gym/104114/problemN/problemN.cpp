#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> s(n + 1), suf(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = s[i];
        if (i + 1 < n) {
            suf[i] = max(suf[i], suf[i + 1] - m);
        }
    }
    int prev = 0;
    for (int i = 0; i < n; i++) {
        int ans = s[i];         // suf[i] already handles this but still kept it here
        ans = max(ans, prev - m);
        ans = max(ans, suf[i]);
        cout << ans << " ";
        prev = ans;
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

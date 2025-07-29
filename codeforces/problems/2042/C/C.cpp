#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> suf(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] + (s[i] == '1' ? 1 : -1);
    }
    suf.pop_back();
    suf.erase(suf.begin());
    sort(suf.rbegin(), suf.rend());
    int cur = 0, ans = -1;
    for (int i = 0; i < int(suf.size()); i++) {
        if (suf[i] < 0) break;  // in the negatives, so we won't reach K (could have just used 64 bits instead)
        cur += suf[i];
        if (cur >= k) {
            ans = i + 2;
            break;
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

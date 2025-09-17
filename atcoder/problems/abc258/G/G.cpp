#include <bits/stdc++.h>
using namespace std;

using B = bitset<3001>;

void solve() {
    int n;
    cin >> n;
    vector<B> A(n);
    for (auto &bs: A) {
        string s;
        cin >> s;
        for (int i = 0; i < n; i++) {
            bs[i] = s[i] == '1';
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        // either start on i + 1 or divide each i's contribution by 2
        // or instead divide everyone at the same time
        for (int j = i + 1; j < n; j++) {
            if (!A[i][j]) continue;
            ans += (A[i] & A[j]).count();
        }
    }
    cout << ans / 3 << '\n';
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int cnta = 0, cntb = 0;
    int fst;
    cin >> fst;
    fst = abs(fst);
    for (int i = 1; i < n; i++) {
        int ai;
        cin >> ai;
        ai = abs(ai);
        if (fst < ai) cnta++;
        else cntb++;
    }
    int need_for_win = (n - 1) / 2;
    string ans;
    if (cnta >= need_for_win) {
        ans = "YES";
    }
    else ans = "NO";
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

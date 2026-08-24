#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    bool yes = n <= k && k <= 2*n-1;
    cout << (yes ? "YES" : "NO") << '\n';
    if (yes) {
        int slack = 2*n-1 - k;
        vector<int> ans; ans.reserve(2*n);
        for (int cur = 0; cur < slack; cur++) {
            int i = n - cur;
            ans.push_back(i);
            ans.push_back(i);
        }
        if (n - slack > 0) {
            int fst = 1; // first not complete (1, 2, ...)
            int snd = min(2, n - slack); // important here (case k = n)
            ans.push_back(fst);
            ans.push_back(snd++);
            for (int i = 0; i < n - slack - 1; i++) {
                snd = min(snd, n - slack);
                ans.push_back(snd++);
                ans.push_back(fst++);
            }
        }
        for (auto &x: ans) cout << x << " ";
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> c(n);
    const int MAX = int(5e3);
    vector<int> cnt(MAX + 1);
    for (int i = 0; i < n; i++) {
        int ci;
        cin >> ci;
        cnt[ci]++;
    }
    bool ans = true;
    for (int i = 2; i <= MAX && ans; i++) {
        if (cnt[i] == 0) continue;
        int64_t total = 0;
        for (int j = 1; j < i && total < i; j++) {
            total += int64_t(j) * cnt[j];
        }
        if (total < i) {
            ans = false;
        }
    }
    cout << (ans ? "YES" : "NO") << '\n';
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

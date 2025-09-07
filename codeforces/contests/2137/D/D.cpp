#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> b(n);
    for (auto &bi: b) cin >> bi;
    vector<int> cur(n + 1), freq(n + 1);
    vector<int> a(n);
    int nxt = 1;
    for (int i = 0; i < n; i++) {
        if (cur[b[i]] == 0) {
            cur[b[i]] = nxt++;
        }
        a[i] = cur[b[i]];
        freq[cur[b[i]]]++;
        if (freq[cur[b[i]]] == b[i]) {
            cur[b[i]] = 0;
        }
    }
    bool valid = nxt <= n + 1;
    for (int i = 0; i <= n; i++) {
        if (cur[i] > 0) {
            valid = false;  // didn't end up finishing this one
        }
    }
    if (valid) {
        for (int v: a) {
            cout << v << " ";
        }
        cout << '\n';
    }
    else {
        cout << "-1\n";
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++) {
        pos[a[i]] = i;
    }
    for (int i = n - 1; i >= 2; i--) {
        if (b[i] == a[i]) continue;
        else {
            // get position of b[i] in a
            int j = pos[b[i]];
            pos[a[i]] = j;
            pos[a[j]] = i;  // unnecessary
            swap(a[j], a[i]);
            int to_swap;
            if (j == i - 1) {
                to_swap = j - 1;
            }
            else {
                to_swap = j + 1;
            }
            pos[a[j]] = to_swap;
            pos[a[to_swap]] = j;
            swap(a[to_swap], a[j]);
        }
    }
    bool ans = a[0] == b[0]; // the other is forced
    cout << (ans ? "Possible" : "Impossible") << '\n';
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) { 
        solve();
    }
    return 0;
}

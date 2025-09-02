#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    set<int> vis;
    int j = n;
    for (int i = n; i >= 1; i--) {
        if (vis.count(b[j])) {
            break;
        }
        if (a[i] == b[j]) {
            j--;
        }
        else {
            vis.insert(a[i]);
        }
    }
    cout << j << '\n';
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
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    pair<int,int> ans = {0, 0};
    int mn = 0;
    for (int i = 0; i < n; i++) {
        int s = 0, l = 0;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) s++;
            else if (a[j] > a[i]) l++;
            if (l - s < mn) {
                mn = l - s;
                ans = {i, j};
            }
        }
    }
    cout << ans.first + 1 << " " << ans.second + 1 << '\n';
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

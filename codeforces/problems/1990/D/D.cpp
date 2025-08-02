#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int last = -1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            last = -1;
        }
        else {
            if (a[i] <= 2) {
                if (last == 1) {
                    last = -1;
                }
                else {
                    ans++;
                    last = 1;
                }
            }
            else if (a[i] <= 4 && last != -1) {
                if (last == 1) {
                    ans++;
                    last = 3;
                }
                else if (last == 3) {
                    ans++;
                    last = 1;
                }
                else exit(1);
            }
            else {
                ans++;
                last = -1;
            }
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

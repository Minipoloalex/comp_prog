#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<pair<int,int>> vals(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vals[i] = {a[i], -i};
    }
    sort(vals.rbegin(), vals.rend());
    vector<bool> covered(n);
    auto cover = [&](int i) {
        covered[i] = 1;
        if (a[i] == 2) {
            for (int j = i + 1; j < n; j++) {
                covered[j] = 1;
                if (a[j] == 0) break;
            }
            for (int j = i - 1; j >= 0; j--) {
                covered[j] = 1;
                if (a[j] == 0) break;
            }
        }
        else if (a[i] == 1) {
            if (i > 0) {
                assert(a[i - 1] == 0);
                if (covered[i - 1]) {
                    for (int j = i + 1; j < n; j++) {
                        covered[j] = 1;
                        if (a[j] == 0) break;
                    }
                }
                else {
                    covered[i - 1] = 1;
                    for (int j = i + 1; j < n && a[j] == 1; j++) {
                        covered[j] = 1;
                    }
                }
            }
            else {
                for (int j = i + 1; j < n; j++) {
                    covered[j] = 1;
                    if (a[j] == 0) break;
                }
            }
        }
    };
    int ans = 0;
    for (auto &[v, negidx]: vals) {
        int i = -negidx;
        if (covered[i]) continue;
        ans++;
        cover(i);
    }
    cout << ans << '\n';
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

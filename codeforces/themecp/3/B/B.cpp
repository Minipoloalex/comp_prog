#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    int64_t total = 0;
    for (auto &x: a) {
        cin >> x;
        total += x;
    }
    vector<int> cur;
    vector<int> vis(n, 0);
    int cur_x = -1;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            i--;
            if (cur_x == -1) {
                total += x - a[i];
                a[i] = x;
            }
            else {
                cur.push_back(i);
                if (!vis[i]) {
                    total += x - cur_x;
                }
                else {
                    total += x - vis[i];
                }
                vis[i] = x;
            }
        }
        else {
            assert(t == 2);
            int x;
            cin >> x;
            cur_x = x;
            for (int c: cur) {
                vis[c] = 0;
            }
            cur.clear();
            total = int64_t(n) * cur_x;
        }
        cout << total << '\n';
    }
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    map<int,int> m;
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        m[ai]++;
    }

    int last_certain = -1;
    bool ans = false;
    for (auto &[v, cnt]: m) {
        if (cnt >= 4) {
            ans = true;
            break;
        }
        if (last_certain == v) {
            if (cnt == 1) {
                last_certain = v + 1;
            }
            else {
                assert(cnt > 0);
                ans = true;
                break;
            }
        }
        else if (cnt >= 2) {
            last_certain = v + 1;
        }
    }
    cout << (ans ? "Yes" : "No") << '\n';
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

#include <bits/stdc++.h>
using namespace std;

#define sz(v) int((v).size())

void solve() {
    int n, d;
    cin >> n >> d;
    vector<vector<int>> occ(n);
    for (int i = 0; i < n; i++) {
        int pi;
        cin >> pi;
        occ[pi].push_back(i);
    }
    int ans = n;
    for (int i = 0; i < n; i++) {
        if (occ[i].empty()) {
            ans = i;
            break;
        }
        vector<pair<int,int>> groups = {{occ[i][0], occ[i][0]}};
        for (int j = 1; j < sz(occ[i]); j++) {
            int prv = groups.back().second;
            int cur = occ[i][j];
            if (cur - prv <= d) {
                groups.back().second = cur;
            }
            else {
                groups.emplace_back(cur, cur);
            }
        }
        int lst = -1;
        bool yes = true;
        for (auto &[l, r]: groups) {
            int SZ = r - l + 1;
            if (SZ > d) {
               yes = false;
               break;
            }
            else {
                if (lst == -1) {
                    lst = max(r, d-1);
                }
                else {
                    if (lst + d >= l) {
                        yes = false;
                        break;
                    }
                    lst = max(r, lst + 2*d);
                }
            }
        }
        if (yes) {
            ans = i;
            break;
        }
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

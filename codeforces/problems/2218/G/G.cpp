#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 676767677;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> b(n);
    vector<vector<int>> tm(m);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        tm[b[i]].push_back(i);
    }
    auto get_neigh = [&](int j, int id) {
        // gets the minimum time when a neighbor sat down
        int mn = INT_MAX;
        if (id - 1 >= 0 && b[id-1] < j) {
            mn = min(mn, b[id-1]);
        }
        if (id + 1 < n && b[id+1] < j) {
            mn = min(mn, b[id+1]);
        }
        return mn;
    };
    int64_t ans = 1;
    int prv = 0, cur = 0; // previous and current number of people
    for (int j = 0; j < m; j++) {
        for (int id: tm[j]) {
            int prv_nsat = get_neigh(j, id);
            if (j == 0) {
                // must be 0
            }
            else if (prv_nsat != INT_MAX) { // neighbor has sat down
                if (prv_nsat == j - 1) {
                    // means that first neighbor just sat down, so we could have any value of ai in [1, cur sat down]
                    // trigger was neighbor sitting
                    ans = ans * cur % MOD;
                }
                else {
                    // sat down long ago (trigger was ppl sitting down): must be in [prv+1, cur sat down]
                    ans = ans * (cur-prv) % MOD;
                }
            }
            else {
                ans = 0;
            }
        }
        prv = cur;
        cur += int(tm[j].size());
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

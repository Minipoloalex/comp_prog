#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> p(n);
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        pos[p[i]] = i;
    }
    auto get_ans = [&](int l, int r, int k) -> int {
        int cnt_need_L = 0, cnt_need_S = 0;
        int cntS = k, cntL = n - cntS - 1;
        while (l < r) {
            int m = (l + r) / 2;
            int vm = p[m];
            if (m < pos[k]) {
                // need to go right
                l = m + 1;
                if (vm > k) {
                    // would go left: needs to be changed
                    // make it smaller
                    cnt_need_S++;
                }
                else {
                    // vm < k
                    cntS--;
                }
            }
            else if (m > pos[k]) {  // go left
                r = m - 1;
                if (vm < k) {
                    // would go right: needs to be changed
                    // make it bigger
                    cnt_need_L++;
                }
                else {
                    // vm > k
                    cntL--;
                }
            }
            else {
                break;
            }
        }
        if (cntL < cnt_need_L || cntS < cnt_need_S) {
            return -1;
        }
        int mn = min(cnt_need_L, cnt_need_S);
        int mx = max(cnt_need_L, cnt_need_S);
        return mn * 2 + (mx - mn) * 2;
    };
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        l--;r--;k--;
        int ans;
        if (pos[k] < l || pos[k] > r) {
            ans = -1;
        }
        else {
            ans = get_ans(l, r, k);
        }
        cout << ans << " ";
    }
    cout << '\n';
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

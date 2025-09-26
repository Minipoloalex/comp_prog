#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, mn, mx;
    cin >> n >> k >> mn >> mx;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    int64_t ans = 0;
    map<int,int> atleast, atmost;
    int cnt_atleast = 0, cnt_atmost = 0;
    int r1 = 0, r2 = 0;
    for (int l = 0; l < n; l++) {
        while (r1 < n && cnt_atleast < k) {
            if (atleast[a[r1]]++ == 0) {
                cnt_atleast++;
            }

            // later test the code without this
            if (r1 == r2) {
                if (atmost[a[r2]]++ == 0) {
                    cnt_atmost++;
                }
                r2++;
            }

            r1++;
        }
        while (r2 < n && cnt_atmost <= k) {
            if (atmost[a[r2]] == 0 && cnt_atmost == k) break;

            if (atmost[a[r2]]++ == 0) {
                cnt_atmost++;
            }
            r2++;
        }
        if (cnt_atmost < k) break;  // ensure there's enough

        // ans += r2 - r1 + 1;
        int rig = min(r2, l + mx);
        int lef = max(r1, l + mn);
        if (lef <= rig) {
            ans += rig - lef + 1;
        }
        if (--atleast[a[l]] == 0) {
            cnt_atleast--;
        }
        if (--atmost[a[l]] == 0) {
            cnt_atmost--;
        }
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

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,greater<int>,rb_tree_tag,tree_order_statistics_node_update>

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto &pi: p) cin >> pi;
    ordered_set pref, suf;
    for (int i = 0; i < n; i++) {
        suf.insert(p[i]);
    }
    for (int i = 0; i < n; i++) {
        suf.erase(p[i]);
        int cnt1 = int(pref.order_of_key(p[i])) - int(pref.order_of_key(2 * n - p[i]));
        int cnt2 = int(suf.order_of_key(p[i]));
        if (cnt1 > cnt2) {
            p[i] = 2 * n - p[i];
        }
        pref.insert(p[i]);
    }
    ordered_set s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cnt_greater_before = int(s.order_of_key(p[i]));
        s.insert(p[i]);
        ans += cnt_greater_before;
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

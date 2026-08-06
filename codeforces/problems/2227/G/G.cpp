#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// multiset: tree<pair<int,int>, null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>
#define os tree<pair<int64_t,int>, null_type,less<pair<int64_t,int>>,rb_tree_tag,tree_order_statistics_node_update>

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;

    os even, odd;

    int id = 0;
    odd.insert({0, id++});
    int64_t pfeven = 0, pfodd = 0;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int cnt;
        if (i & 1) { // i odd
            pfeven += a[i];
            pfodd -= a[i];
            cnt = int(even.order_of_key({pfeven, -1})); // strictly smaller so 0 as id would also work

            odd.insert({pfodd, id++});
            // even.insert({pfeven, id++});
        }
        else { // i even
            pfeven -= a[i];
            pfodd += a[i];

            cnt = int(odd.order_of_key({pfodd, -1}));

            // odd.insert({pfodd, id++});
            even.insert({pfeven, id++});
        }
        ans += cnt;
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

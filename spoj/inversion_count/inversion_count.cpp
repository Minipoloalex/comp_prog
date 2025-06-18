#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// numbers are distinct
#define ordered_set tree<int, null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>

void solve() {
    int n;
    cin >> n;
    ordered_set os;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int ai;
        cin >> ai;
        ans += i - os.order_of_key(ai); // no worries since all distinct numbers
        os.insert(ai);
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

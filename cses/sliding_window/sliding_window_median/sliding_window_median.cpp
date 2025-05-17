#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ordered_set tree<pair<int,int>, null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    int idx = (k - 1) / 2;
    ordered_set os;
    for (int i = 0; i < n; i++) {
        os.insert({x[i], i});
        if (int(os.size()) > k) {
            os.erase(os.find({x[i - k], i - k}));
        }
        if (int(os.size()) == k) {
            cout << (os.find_by_order(idx)->first) << " \n"[i == n - 1];
        }
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

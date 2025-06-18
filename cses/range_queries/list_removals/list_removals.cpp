#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

// multiset: tree<pair<int,int>, null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>
#define ordered_set tree<int, null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>

void solve() {
    int n;
    cin >> n;
    vector<int> x(n), k(n);
    for (auto &xi: x) cin >> xi;
    for (auto &ki: k) cin >> ki;
    ordered_set os;
    for (int i = 0; i < n; i++) {
        os.insert(i);
    }
    for (int i = 0; i < n; i++) {
        int idx = *os.find_by_order(k[i] - 1);
        os.erase(idx);
        cout << x[idx] << " \n"[i == n - 1];
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

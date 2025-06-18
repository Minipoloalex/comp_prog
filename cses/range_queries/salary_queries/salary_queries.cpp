#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

// need multiset
#define ordered_set tree<pair<int,int>, null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> p(n);
    ordered_set os;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        os.insert({p[i], i});
    }

    auto rsq = [&](int a, int b) {
        int ra = (int) os.order_of_key({a, 0});    // |values| < a
        int rb = (int) os.order_of_key({b, INT_MAX});  // |values| <= b
        return rb - ra;
    };
    while (q--) {
        char c;
        cin >> c;
        if (c == '!') {
            int k, x;
            cin >> k >> x;
            k--;
            os.erase({p[k], k});
            p[k] = x;
            os.insert({p[k], k});
        }
        else {
            assert(c == '?');
            int a, b;
            cin >> a >> b;
            cout << rsq(a, b) << '\n';
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

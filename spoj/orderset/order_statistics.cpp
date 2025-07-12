#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using os = ordered_set<int>;

void solve() {
    int q;
    cin >> q;
    os s;
    while (q--) {
        char c;
        cin >> c;
        int x;
        cin >> x;
        if (c == 'I') {
            s.insert(x);
        }
        else if (c == 'D') {
            s.erase(x);
        }
        else if (c == 'K') {
            int k = x;
            k--;
            auto it = s.find_by_order(k);
            if (it == s.end()) {
                cout << "invalid" << '\n';
            }
            else cout << *it << '\n';
        }
        else {
            assert(c == 'C');
            int smaller_than_x = int(s.order_of_key(x));
            cout << smaller_than_x << '\n';
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

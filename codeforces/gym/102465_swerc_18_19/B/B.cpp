#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> left(n), right(n);
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        left[i] = x;
        right[i] = n - y - 1;
    }

    auto get = [&] (int side) -> bool {
        multiset<int> max_left, max_right;
        for (int i = 0; i < side; i++) {
            max_left.insert(left[i]);
            max_right.insert(right[i]);
        }

        for (int i = side; i <= n; i++) {
            // check if can
            int mx_l = *max_left.rbegin();
            int mx_r = *max_right.rbegin();

            if (n - (mx_l + mx_r) >= side) return true;

            // update multisets
            max_left.erase(max_left.find(left[i - side]));
            max_right.erase(max_right.find(right[i - side]));
            if (i < n) {
                max_left.insert(left[i]);
                max_right.insert(right[i]);
            }
        }

        return false;
    };  

    int l = 1, r = n;
    while (l < r) {
        int m = (l + r + 1) / 2;
        if (get(m)) l = m;
        else r = m - 1;
    }

    cout << l << endl;
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    int64_t total = 0, cur_value = 0, acc_value = 0;
    for (int i = n - 1; i >= 0; i--) {
        // cout << i << " " << cur_value << " " << acc_value << " " << total << endl;
        if (acc_value + cur_value >= 0) {
            // split i with (i + 1)
            acc_value += cur_value;
            total += acc_value;
            cur_value = a[i];
        }
        else {
            cur_value += a[i];
            // do not split
        }
        // cout << i << " " << cur_value << " " << acc_value << " " << total << endl;
    }
    acc_value += cur_value;
    total += acc_value;
    cout << total << '\n';
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

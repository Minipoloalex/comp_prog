#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int,int>> before;
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        bool valid = true;
        for (auto &[l, r]: before) {
            if (a == l || a == r) continue;
            if (b == l || b == r) continue;
            if (b <= l) continue;
            if (a >= r) continue;
            if (a >= l && b <= r) continue;
            if (a <= l && b >= r) continue;
            valid = false;
            break;
        }
        if (valid) {
            before.emplace_back(a, b);
        }
        cout << (valid ? "Yes" : "No") << '\n';
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

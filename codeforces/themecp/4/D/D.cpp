#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    auto ask = [&](int r, int c) {
        if (r > n || c > m) assert(false);
        cout << "? " << r << " " << c << endl;
        int ans;
        cin >> ans;
        return ans;
    };
    auto finish = [](int r, int c) {
        cout << "! " << r << " " << c << endl;
    };

    int d11 = ask(1, 1);
    int k = 1 + d11;
    if (k <= m) {
        int d1k = ask(1, k);
        if (d1k < d11) {
            finish(1 + d1k, k);
            return;
        }
    }
    if (k <= n) {
        int dk1 = ask(k, 1);
        if (dk1 < d11) {
            finish(k, 1 + dk1);
            return;
        }
    }
    finish(k, k);
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

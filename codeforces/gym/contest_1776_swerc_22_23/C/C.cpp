#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    sort(x.rbegin(), x.rend());
    bool A_wins = true;
    int k = -1;
    for (int i = 0; i < n; i++) {
        int sz = i + 1;
        if (1LL * x[i] * sz > m) {
            // means B wins
            A_wins = false;
            k = x[i];
            break;
        }
    }
    vector<bool> filled(m + 1);
    if (A_wins) {
        cout << "Alessia" << endl;
        for (int i = 0; i < n; i++) {
            int y = x[i];
            int a = -1;
            int cur = 0;
            for (int j = 1; j <= m; j++) {
                if (filled[j]) {
                    cur = 0;
                }
                else {
                    cur++;
                }
                if (cur >= y) {
                    a = j - y + 1;
                    break;
                }
            }
            assert(a != -1);
            cout << y << " " << a << endl;
            int b;
            cin >> b;
            filled[b] = true;
        }
    }
    else {
        cout << "Bernardo" << endl;
        assert(k != -1);
        for (int i = 0; i < n; i++) {
            int y, a;
            cin >> y >> a;
            int b = -1;
            for (int j = a; j < y + a; j++) {
                if (filled[j]) {
                    b = j;
                    break;
                }
                if (b == -1 && j % k == 0) {
                    b = j;
                }
            }
            if (b == -1) {
                b = a;  // already won here
            }
            filled[b] = true;
            cout << b << endl;
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

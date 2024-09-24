#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int mx = 0;
        for (int i = 0; i < n; i++) {
            int ai;
            cin >> ai;
            mx = max(mx, ai);
        }
        while (m--) {
            char c;
            int l, r;
            cin >> c >> l >> r;
            if (l <= mx && mx <= r) {
                if (c == '+') {
                    mx++;
                }
                else {
                    assert(c == '-');
                    mx--;
                }
            }
            cout << mx << " ";
        }
        cout << '\n';
    }
    return 0;
}

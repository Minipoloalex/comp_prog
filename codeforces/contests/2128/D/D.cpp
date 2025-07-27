#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];
    vector<int64_t> ans(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (i - 2 >= 1) {
            if ((p[i - 2] > p[i - 1] && p[i - 1] > p[i]) || 
                (p[i - 2] < p[i]) || (p[i - 2] > p[i] && p[i - 1] > p[i])
            ) {
                ans[i] = ans[i - 1] + i - 1 + 1;
            }
            else {
                ans[i] = ans[i - 1] + 1;
            }
        }
        else if (i - 1 >= 1) {
            ans[i] = ans[i - 1] + 1;
            if (p[i - 1] > p[i]) {
                ans[i] += i - 1;
            }
        }
        else {
            ans[i] = 1;
        }
    }
    int64_t res = 0;
    for (int i = 1; i <= n; i++) {
        res += ans[i];
    }
    cout << res << '\n';
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int cur_large = n*n, cur_small = 1;
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < n; j++) {
                if ((i + j) % 2 == 0) {
                    ans[i][j] = cur_small++;
                }
                else {
                    ans[i][j] = cur_large--;
                }
            }
        }
        else {
            for (int j = n - 1; j >= 0; j--) {
                if ((i + j) % 2 == 0) {
                    ans[i][j] = cur_small++;
                }
                else {
                    ans[i][j] = cur_large--;
                }
            }
        }
    }
    for (auto &v: ans) {
        for (int val: v) cout << val << " ";
        cout << '\n';
    }
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

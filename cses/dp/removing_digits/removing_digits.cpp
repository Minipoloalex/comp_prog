#include <bits/stdc++.h>
using namespace std;

vector<int> get_digits(int x) {
    vector<int> ans;
    while (x) {
        ans.push_back(x % 10);
        x /= 10;
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<int> cost(n + 1, INT_MAX);
    cost[0] = 0;
    for (int i = 1; i <= n; i++) {
        vector<int> digits = get_digits(i);
        for (int d: digits) {
            if (d > 0) {
                cost[i] = min(cost[i], cost[i - d] + 1);
            }
        }
    }
    cout << cost[n] << '\n';
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

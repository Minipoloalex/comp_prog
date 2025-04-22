#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    stack<int> s;   // stuff inside is always ascending (from bot to top of stack)
    // stack has indices that are possible answers for the future
    for (int i = 0; i < n; i++) {
        int ans = 0;
        while (!s.empty() && x[i] <= x[s.top()]) {
            s.pop();
        }
        if (!s.empty()) ans = s.top() + 1;
        s.push(i);
        cout << ans << " \n"[i == n - 1];
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

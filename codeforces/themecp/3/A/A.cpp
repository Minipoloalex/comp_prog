#include <bits/stdc++.h>
using namespace std;

int n, m;

bool dfs(int i) {
    if (i == m) return true;
    if (i % 3 != 0) return false;
    int x = i / 3;
    int y = i - x;
    bool ans = false;
    ans |= dfs(x);
    ans |= dfs(y);
    return ans;
}

void solve() {
    cin >> n >> m;
    cout << (dfs(n) ? "YES" : "NO") << '\n';
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

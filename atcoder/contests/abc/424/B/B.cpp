#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> solves(n);
    vector<int> ans;
    while (k--) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        solves[a]++;
        if (solves[a] == m) {
            ans.push_back(a);
        }
    }
    for (int v: ans) {
        cout << v + 1 << " ";
    }
    cout << '\n';
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

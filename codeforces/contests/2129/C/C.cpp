#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<array<int,3>> v(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v[i] = {a, b, i};
    }
    int curl = 0, curr = 0;
    sort(v.begin(), v.end());
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        auto &[a, b, idx] = v[i];
        if (b > curr) {
            ans.push_back(idx);
            curr = b;
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int a: ans) cout << a + 1 << " ";
    cout << '\n';
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

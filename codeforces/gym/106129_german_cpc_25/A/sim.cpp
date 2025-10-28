#include <bits/stdc++.h>
using namespace std;

void solve() {
    for (int l = 2; l <= 10; l++) {
        for (int r = 1; r <= 10; r++) {
            int n = l + r;
            vector<int> up(n + 1), down;
            for (int i = 1; i <= n; i++) up[i-1] = i;
            up[n] = 1;

            for (int i = l + 1; i <= n; i++) down.push_back(i);
            for (int i = 1; i <= l; i++) down.push_back(i);

            set<array<int, 2>> st;

            for (int i = 0; i < n; i++) {
                st.insert({min(up[i], down[i]), max(up[i], down[i])});
                st.insert({min(up[i+1], down[i]), max(up[i+1], down[i])});
            }

            cout << l << ' ' << r << " -> " << st.size() << endl;
        }
        cout << endl;
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

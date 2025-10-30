#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    set<int> a;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a.insert(ai);
    }
    cout << a.size() * 2 - 1 << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

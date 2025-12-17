#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    map<int,int> f1, f2;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        f1[x]++;
        f2[x+y]++;
    }
    int xans = INT_MAX;
    for (auto &[x, f]: f1) {
        if (f & 1) {
            xans = x;
        }
    }
    int valans = INT_MAX;
    for (auto &[v, f]: f2) {
        if (f & 1) {
            valans = v;
        }
    }
    assert(xans != INT_MAX && valans != INT_MAX);
    cout << xans << " " << valans - xans << '\n';
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

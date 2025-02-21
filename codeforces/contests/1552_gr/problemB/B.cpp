#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<array<int,5>> r(n);
    for (auto &a: r) {
        for (int i = 0; i < 5; i++) cin >> a[i];
    }
    auto better = [&](int a, int b) {
        int cnta = 0;
        for (int i = 0; i < 5; i++) {
            cnta += r[a][i] < r[b][i];
        }
        return cnta >= 3;
    };
    int w = 0;
    for (int i = 1; i < n; i++) {
        if (better(i, w)) w = i;
    }
    bool yes = true;
    for (int i = 0; i < n; i++) {
        if (i == w) continue;
        yes &= better(w, i);
    }
    if (!yes) {
        w = -2;
    }
    cout << w + 1 << '\n';
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b;
    for (auto &ai: a) cin >> ai;
    bool good = false;
    for (int i = 1; i < n; i++) {
        if (abs(a[i] - a[i - 1]) <= 1) {
            good = true;
        }
    }
    if (good) {
        cout << "0\n";
        return;
    }
    b = a;
    sort(b.begin(), b.end());
    bool eq = false;
    if (b == a) eq = true;
    reverse(b.begin(), b.end());
    if (b == a) eq = true;
    if (eq) {
        cout << "-1\n";
    }
    else cout << "1\n";
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

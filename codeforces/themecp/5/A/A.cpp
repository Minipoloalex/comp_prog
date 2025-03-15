#include <bits/stdc++.h>
using namespace std;

bool solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x: a) cin >> x;
    int mx = *max_element(a.begin(), a.end());
    int idx = int(find(a.begin(), a.end(), mx) - a.begin());
    for (int i = 0; i < idx; i++) {
        if (a[i] > a[i + 1]) return false;
    }
    for (int i = idx + 1; i < n; i++) {
        if (a[i] > a[i - 1]) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        cout << (solve() ? "YES" : "NO") << '\n';
    }
    return 0;
}

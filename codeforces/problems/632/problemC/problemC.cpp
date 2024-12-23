#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto &x: s) cin >> x;
    sort(s.begin(), s.end(), [](const string &a, const string &b) {
        return a + b < b + a;
    });
    for (string x: s) cout << x;
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

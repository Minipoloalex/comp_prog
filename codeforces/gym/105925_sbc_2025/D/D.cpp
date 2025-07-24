#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string s, t;
    cin >> s >> t;

    auto cnt_s = count_if(s.begin(), s.end(), [](char c) { return c == '*'; });
    auto cnt_t = count_if(t.begin(), t.end(), [](char c) { return c == '*'; });

    cout << fixed << setprecision(2) << double(cnt_s - cnt_t) / double(cnt_s) << '\n';
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

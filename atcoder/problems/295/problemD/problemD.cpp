#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());

    map<int, int> freq = {make_pair(0, 1)};
    int pref = 0;
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - '0';
        pref ^= 1 << c;
        ans += freq[pref];
        freq[pref]++;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

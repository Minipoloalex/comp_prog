#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto &pi: p) cin >> pi;
    int l = int(find(p.begin(), p.end(), n) - p.begin());
    int r = l;
    int nxt = n - 1;
    bool ans = true;
    while (nxt >= 1) {
        bool good = false;
        if (l > 0 && p[l-1] == nxt) {
            l--;
            good = true;
        }
        else if (r + 1 < n && p[r+1] == nxt) {
            r++;
            good = true;
        }
        if (!good) {
            ans = false;
            break;
        }
        nxt--;
    }
    cout << (ans ? "YES": "NO") << '\n';
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

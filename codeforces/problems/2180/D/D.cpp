#include <bits/stdc++.h>
using namespace std;

void solve() {
    auto inters = [&](int la, int ra, int lb, int rb) {
        return pair<int,int>{max(la, lb), min(ra, rb)};
    };
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    vector<int> sm(n), big(n);
    int ans = 0;
    for (int i = 1; i < n; i++) {
        int d = x[i] - x[i-1];
        int prvs = sm[i-1];
        int prvb = big[i-1];
        tie(prvs, prvb) = inters(prvs, prvb, 0, d);
        if (i == 1) {
            sm[i] = 0;
            big[i] = d;
        }
        else if (prvs >= prvb) {
            ans--;
            // doesn't matter to update the sm and big on this one
            sm[i] = 0;
            big[i] = d;
        }
        else {
            sm[i] = d - prvb;
            big[i] = d - prvs;
        }
        ans++;
    }
    cout << ans << '\n';
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

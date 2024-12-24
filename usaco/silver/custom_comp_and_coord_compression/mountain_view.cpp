#include <bits/stdc++.h>
using namespace std;

void solve() {
    freopen("mountains.in", "r", stdin);
    freopen("mountains.out", "w", stdout);
    int n;
    cin >> n;
    vector<pair<int,int>> mountains(n);
    for (auto &m: mountains) {
        int x, y;
        cin >> x >> y;
        m = make_pair(x - y, x + y);
    }
    sort(mountains.begin(), mountains.end(), [](const pair<int,int> &p1, const pair<int,int> &p2) {
        return make_pair(p1.first, -p1.second) < make_pair(p2.first, -p2.second);
    });
    // for (auto &[l, r]: mountains) {
    //     cout << l << " " << r << ", ";
    // }
    // cout << endl;

    auto &[pl, pr] = mountains[0];
    int ans = 1;
    for (int i = 1; i < n; i++) {
        auto &[l, r] = mountains[i];
        if (l > pr) {
            pl = l;
            pr = r;
            ans++;
        }
        else {
            if (r > pr) {
                ans++;
                pr = r; // same pl
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

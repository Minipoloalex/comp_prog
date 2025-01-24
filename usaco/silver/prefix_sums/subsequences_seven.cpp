#include <bits/stdc++.h>
using namespace std;

const int MOD = 7;

typedef pair<int, int> ii;

void solve() {
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);
    int n;
    cin >> n;
    vector<int64_t> pref(n);
    vector<ii> mods(7, make_pair(INT_MAX, 0));
    for (int i = 0; i < n; i++) {
        cin >> pref[i];
        if (i - 1 >= 0) {
            (pref[i] += pref[i - 1]) %= MOD;
        }
        mods[pref[i]].first = min(mods[pref[i]].first, i);
        mods[pref[i]].second = max(mods[pref[i]].second, i);
    }
    int ans = 0;
    for (int i = 0; i < 7; i++) {
        ans = max(ans, mods[i].second - mods[i].first);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
}

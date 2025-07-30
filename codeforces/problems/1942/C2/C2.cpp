#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> v(x);
    for (auto &vi: v) cin >> vi;
    sort(v.begin(), v.end());
    vector<int> even, odd;
    int ans = 0;
    for (int i = 0; i < x; i++) {
        int cur = v[i];
        int nxt = v[(i + 1) % x];
        if (nxt < cur) {
            nxt += n;
        }
        int diff = nxt - cur;
        if (diff > 2) {
            if (diff % 2 == 0) even.push_back(diff);
            else odd.push_back(diff);
        }
        else {
            if (diff == 2) {
                ans++;
            }
        }
    }
    auto complete = [](int sides) {
        return sides - 2;
    };
    sort(even.begin(), even.end());
    int cur = 0;
    for (int d: even) {
        if (cur == y) {
            break;
        }
        int need = d / 2 - 1;
        if (cur + need <= y) {
            cur += need;
            ans += complete(d + 1);
        }
        else {
            int mx = y - cur;
            cur += mx;
            ans += mx * 2;
        }
    }
    for (int d: odd) {
        if (cur == y) break;
        int need = d / 2;
        int mx = min(y - cur, need);
        cur += mx;
        ans += mx * 2;
    }
    ans += complete(x);
    cout << ans << '\n';
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

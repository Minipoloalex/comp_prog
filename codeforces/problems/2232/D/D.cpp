#include <bits/stdc++.h>
using namespace std;

const int MX_N = 20;
int n;
int a[MX_N + 1];

vector<array<int,3>> ans;

void mv(int nr, int f, int h, int t) { // from, helper, target
    if (nr == 0) return;
    int i = nr - 1;

    // cout << i << " " << nr - (a[i] + 1) << endl;
    int cnt_hmv = nr - (a[i] + 1);
    mv(cnt_hmv, f, t, h); // mv this number of layers at the top to h
    ans.push_back({i+1, f, t});
    if (a[i] == 0) {
        // means that f now has nothing on top, so we can use h as f instead
        mv(nr - 1, h, f, t);
    }
    else {
        mv(cnt_hmv, h, t, f);
        mv(nr - 1, f, h, t);
    }
}

void solve() {
    ans.clear();
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    bool yes = true;
    for (int i = 0; i < n; i++) {
        if (a[i] > i) {
            yes = false;
        }
    }
    cout << (yes ? "YES" : "NO") << '\n';
    if (yes) {
        mv(n, 1, 2, 3);
        cout << ans.size() << '\n';
        for (auto &[id, f, t]: ans) {
            cout << id << " " << f << " " << t << '\n';
        }
    }

}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    ans.reserve(1 << 20);
    while (t--) {
        solve();
    }
    return 0;
}

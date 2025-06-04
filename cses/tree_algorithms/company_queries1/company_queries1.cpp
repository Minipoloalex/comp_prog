#include <bits/stdc++.h>
using namespace std;

// my first binary jumping implementation (!!!)
/*
vector<int> v(n - 1);
for (auto &pi: v) cin >> pi;
v.insert(v.begin(), -1);

int sz = (int)ceil(log2(n)) + 1;
vector<vector<int>> pars(n, vector<int>(sz, 0));

for (int i = 1; i < n; i++) {
    pars[i][0] = v[i];
}
for (int p = 1; p < sz; p++) {
    for (int i = 1; i < n; i++) {
        pars[i][p] = pars[pars[i][p - 1]][p - 1];
    }
}
*/
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n - 1);
    for (auto &pi: v) {
        cin >> pi;
        pi--;
    }
    v.insert(v.begin(), -1);

    int sz = (int)ceil(log2(n)) + 1;
    vector<vector<int>> pars(n, vector<int>(sz, -1));

    for (int i = 1; i < n; i++) {
        pars[i][0] = v[i];
    }
    for (int p = 1; p < sz; p++) {
        for (int i = 1; i < n; i++) {
            if (pars[i][p-1] != -1) {
                pars[i][p] = pars[pars[i][p - 1]][p - 1];
            }
        }
    }

    while (q--) {
        int x, k;
        cin >> x >> k;
        x--;
        for (int d = 0; d < sz; d++) {
            if ((1 << d) & k) {
                x = pars[x][d];
            }
            if (x == -1) break;
        }
        if (x != -1) {
            x++;
        }
        cout << x << '\n';
    }
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

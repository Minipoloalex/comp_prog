#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<ii> prefmin(n), sufmin(n);
    for (int i = 0; i < n; i++) {
        prefmin[i] = {a[i], i};
        if (i > 0 && prefmin[i - 1].first < prefmin[i].first) {
            prefmin[i] = prefmin[i - 1];
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        sufmin[i] = {a[i], i};
        if (i + 1 < n && sufmin[i + 1].first < sufmin[i].first) {
            sufmin[i] = sufmin[i + 1];
        }
    }

    int fst = int(min_element(a.begin(), a.end()) - a.begin());
    int l = fst, r = fst;
    int L = l - (a[fst] - 1);
    int R = r + (a[fst] - 1);
    int timer = 1;
    bool ans = true;
    while (ans) {
        int mn = INT_MAX, idx = -1;
        if (l > 0) {
            tie(mn, idx) = prefmin[l - 1];
        }
        if (r + 1 < n) {
            auto [sufmn, sufidx] = sufmin[r + 1];
            if (sufmn < mn)  {
                mn = sufmn;
                idx = sufidx;
            }
        }
        if (mn == INT_MAX) break;

        int d;
        if (idx < l) {
            d = l - idx;
        }
        else {
            d = idx - r;
        }
        timer += d;

        l = min(l, idx);
        r = max(r, idx);

        int vd = a[idx] - timer;
        L = max(L, l - vd);
        R = min(R, r + vd);

        if (vd < 0) {
            ans = false;
            break;
        }
    }
    L = max(0, L);
    R = min(R, n - 1);
    if (ans) {
        cout << max(0, R - L + 1) << '\n';
    }
    else {
        cout << "0\n";
    }
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

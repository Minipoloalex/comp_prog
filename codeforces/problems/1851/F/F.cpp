#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    using vpii = vector<pair<int,int>>;
    vector<vector<pair<int,int>>> groups(1);
    for (int i = 0; i < n; i++) {
        groups[0].emplace_back(a[i], i);
    }
    for (int i = k - 1; i >= 0; i--) {
        auto pref = [&](int v) {
            return v >> i;
        };
        vector<vpii> newgroups;
        for (int j = 0; j < int(groups.size()); j++) {
            // sort numbers by their prefix to allow fast N^2-like comparison
            sort(groups[j].begin(), groups[j].end(), [&](pair<int,int> &l, pair<int,int> &r) {
                return pref(l.first) < pref(r.first);
            });
            vector<pair<int,int>> fst, snd;
            bool on_fst = true;
            fst.push_back(groups[j][0]);
            for (int u = 0; u < int(groups[j].size()) - 1; u++) {
                if (pref(groups[j][u].first) == pref(groups[j][u + 1].first)) {
                    if (on_fst) {
                        fst.push_back(groups[j][u + 1]);
                    }
                    else {
                        snd.push_back(groups[j][u + 1]);
                    }
                }
                else {
                    snd.push_back(groups[j][u + 1]);
                    on_fst = false;
                }
            }
            if (fst.size() > 1) {
                newgroups.push_back(fst);
            }
            if (snd.size() > 1) {
                newgroups.push_back(snd);
            }
        }
        if (newgroups.empty()) {
            auto cut = [&](int val, int bit) {
                int mask = (1 << bit) - 1;
                return val & mask;
            };
            for (int j = 0; j < int(groups.size()); j++) {
                // keep the same groups but remove the entire prefix (including the current bit)
                for (auto &[val, idx]: groups[j]) {
                    val = cut(val, i);
                }
            }
        }
        else {
            groups = newgroups;
        }
    }
    int ansi = min(groups[0][0].second, groups[0][1].second);
    int ansj = max(groups[0][0].second, groups[0][1].second);
    int ansx = 0;
    for (int i = k - 1; i >= 0; i--) {
        int bi = (1 << i) & a[ansi];
        int bj = (1 << i) & a[ansj];
        if (bi == 0 && bj == 0) {
            ansx |= (1 << i);
        }
    }
    // cout << ((ansx ^ a[ansi]) & (ansx ^ a[ansj])) << " ";
    cout << ansi + 1 << " " << ansj + 1 << " " << ansx << '\n';
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

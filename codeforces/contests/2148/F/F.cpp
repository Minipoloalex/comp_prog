#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> vecs(n);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int ki;
        cin >> ki;
        mx = max(mx, ki);
        vecs[i].resize(ki);
        for (int j = 0; j < ki; j++) {
            cin >> vecs[i][j];
        }
    }
    vector<pair<int,vector<int>>> mns(mx, {INT_MAX, {}});
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < int(vecs[i].size()); j++) {
            if (vecs[i][j] < mns[j].first) {
                mns[j].first = vecs[i][j];
                mns[j].second = {i};
            }
            else if (vecs[i][j] == mns[j].first) {
                mns[j].second.push_back(i);
            }
        }
    }
    vector<int> row(mx);
    for (int i = 0; i < mx; ) {
        vector<int> &cands = mns[i].second;
        vector<int> valid(cands.size(), 1);
        bool finish = false;
        int j = i;
        for (; j < mx; j++) {
            int best = INT_MAX;
            for (int k = 0; k < int(cands.size()); k++) {
                if (valid[k]) {
                    if (j >= int(vecs[cands[k]].size())) {
                        finish = true;
                        break;
                    }
                    best = min(best, vecs[cands[k]][j]);
                }
            }
            if (finish) {
                break;
            }
            for (int k = 0; k < int(cands.size()); k++) {
                if (valid[k]) {
                    if (vecs[cands[k]][j] != best) valid[k] = 0;
                }
            }
            row[j] = best;
        }
        i = j;
    }
    for (int v: row) cout << v << " ";
    cout << '\n';
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

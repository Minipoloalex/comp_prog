#include <bits/stdc++.h>
using namespace std;

int ask(int u, int v) {
    cout << u+1 << " " << v+1 << endl;
    int ret;
    cin >> ret;
    return ret;
}

int handle(pair<int,int> &l, pair<int,int> &r) {
    for (int i = l.first; i <= l.second; i++) {
        for (int j = r.first; j <= r.second; j++) {
            if (ask(i, j)) return 1;
        }
    }
    return 0;
}

void solve() {
    int n;
    cin >> n;
    bool done = false;
    vector<pair<int,int>> segs(n);
    for (int i = 0; i < n; i++) {
        segs[i] = {i, i};
    }
    while (!done) {
        vector<pair<int,int>> nsegs;
        for (int i = 0; i < int(segs.size()); i += 2) {
            pair<int,int> pseg, nxtseg;
            if (i + 1 == int(segs.size())) {
                assert(!nsegs.empty());
                pseg = nsegs.back();
                nsegs.pop_back();
                nxtseg = segs[i];
            }
            else {
                pseg = segs[i];
                nxtseg = segs[i+1];
            }
            if (handle(pseg, nxtseg)) {
                done = true;
                break;
            }
            nsegs.emplace_back(pseg.first, nxtseg.second);
        }
        swap(segs, nsegs);
    }
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

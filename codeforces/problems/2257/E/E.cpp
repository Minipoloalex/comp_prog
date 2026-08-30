#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    int64_t x;
    cin >> n >> x;
    vector<vector<int>> a(n);
    vector<vector<int>> b(n);
    for (int i = 0; i < n; i++) {
        int mi; cin >> mi;
        a[i].resize(mi);
        b[i].resize(mi);
        for (auto &aij: a[i]) cin >> aij;
        for (auto &bij: b[i]) cin >> bij;
    }
    using segm = tuple<int64_t,int64_t,int>;
    vector<vector<segm>> p(n);
    for (int i = 0; i < n; i++) {
        int sz = int(a[i].size());
        int64_t cur = 0;
        int64_t curneed = 0;
        for (int j = 0; j < sz; j++) {
            curneed = max(curneed, a[i][j] - cur); // cur <= 0 here
            cur += b[i][j] - a[i][j];
            if (cur > 0) {
                p[i].push_back({curneed, cur, j+1}); // j+1 is exclusive
                curneed = 0;
                cur = 0;
            }
        }
    }
    using item = tuple<int64_t,int64_t,int,int>;
    priority_queue<item,vector<item>,greater<item>> pq;
    vector<int> ids(n, 0); // indices of floors we're at in each building
    vector<int> segidx(n, 0);

    auto push_pq = [&](segm &seg, int i) {
        auto &[need, gain, fidx] = seg;
        pq.push({need, gain, fidx, i});
    };
    for (int i = 0; i < n; i++) {
        if (!p[i].empty()) {
            push_pq(p[i][0], i);
        }
    }
    while (!pq.empty()) {
        auto [need, gain, nxtfidx, bidx] = pq.top(); // want smallest "need"
        pq.pop();
        if (x >= need) { // can take it
            x += gain;
            ids[bidx] = nxtfidx;

            segidx[bidx]++;
            if (segidx[bidx] < int(p[bidx].size())) {
                push_pq(p[bidx][segidx[bidx]], bidx);
            }
        }
        else { // cannot take anything more
            break;
        }
    }
    int ans = 0;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        int64_t cur = x;
        int sz = int(a[i].size());
        int cnt = ids[i];
        for (int j = ids[i]; j < sz; j++) {
            if (cur < a[i][j]) break;
            cur += b[i][j] - a[i][j];
            if (cur < 0) {
                break;
            }
            cnt++;
        }
        if (cnt > ans) {
            ans = cnt;
            idx = i;
        }
    }
    cout << ans << " " << idx + 1 << '\n';
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

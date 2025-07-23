#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

vector<int> lef, rig;
vi x;
vi ans;
vii qs;

// O((N + Q) * log(N))
void div_cq(int l, int r, vi &qids) {
    // all queries inside qs are completely contained within [l, r]
    if (qids.empty()) return;
    if (l == r) {
        for (int qidx: qids) ans[qidx] = x[l];
        return;
    }

    int m = l + (r - l) / 2;
    lef[m] = x[m];
    for (int i = m - 1; i >= l; i--) {
        lef[i] = min(x[i], lef[i + 1]);
    }
    rig[m + 1] = x[m + 1];
    for (int i = m + 2; i <= r; i++) {
        rig[i] = min(rig[i - 1], x[i]);
    }

    array<vi, 2> q;
    for (int qidx: qids) {
        auto &[ql, qr] = qs[qidx];  // ql <= qr

        if (qr <= m) q[0].push_back(qidx);
        else if (ql >= m + 1) {
            q[1].push_back(qidx);
        }
        else {
            // we can answer here
            int qmn = min(lef[ql], rig[qr]);
            ans[qidx] = qmn;
        }
    }
    div_cq(l, m, q[0]);
    div_cq(m + 1, r, q[1]);
}

void solve() {
    int n, q;
    cin >> n >> q;
    x.resize(n);
    lef.resize(n);
    rig.resize(n);
    for (auto &xi: x) cin >> xi;

    qs.resize(q);
    for (auto &[l, r]: qs) {
        cin >> l >> r;
        l--;r--;
    }
    vi qids(q);
    iota(qids.begin(), qids.end(), 0);
    ans.resize(q);

    div_cq(0, n - 1, qids);

    for (int a: ans) cout << a << '\n';
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

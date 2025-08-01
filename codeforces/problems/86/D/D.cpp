#include <bits/stdc++.h>
using namespace std;

const int MAX = int(1e6);

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    using Q = array<int,3>;
    vector<Q> qs(q);
    for (int i = 0; i < q; i++) {
        auto &[l, r, idx] = qs[i];
        idx = i;
        cin >> l >> r;
        l--;
        r--;
    }
    int block_size = 447;
    sort(qs.begin(), qs.end(), [&](const Q &q1, const Q &q2) {
        auto &[l1, r1, _1] = q1;
        auto &[l2, r2, _2] = q2;
        int b1 = l1 / block_size;
        int b2 = l2 / block_size;
        return b1 < b2 || (b1 == b2 && r1 < r2);
    });

    vector<int64_t> ans(q);
    int64_t cur = 0;
    vector<int> freq(MAX + 1, 0);
    auto value = [&](int v) {
        return int64_t(freq[v]) * freq[v] * v;
    };
    auto add = [&](int i) {
        int v = a[i];
        cur -= value(v);
        freq[v]++;
        cur += value(v);
    };
    auto remove = [&](int i) {
        int v = a[i];
        cur -= value(v);
        freq[v]--;
        cur += value(v);
    };
    int mo_left = 0, mo_right = -1;
    for (auto &[l, r, origidx]: qs) {
        while (mo_right < r) add(++mo_right);
        while (mo_right > r) remove(mo_right--);
        while (mo_left > l) add(--mo_left);
        while (mo_left < l) remove(mo_left++);
        ans[origidx] = cur;
    }
    for (int64_t v: ans) cout << v << '\n';
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

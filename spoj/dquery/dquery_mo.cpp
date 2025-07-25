#include <bits/stdc++.h>
using namespace std;

const int MAX = int(1e6);

void solve() {
    int n;
    cin >> n;
    using T = array<int,3>;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int q;
    cin >> q;
    vector<T> qs(q);
    for (int i = 0; i < q; i++) {
        auto &[l, r, idx] = qs[i];
        cin >> l >> r;
        idx = i;
        l--;r--;
    }
    int block_size = int(sqrt(n));
    sort(qs.begin(), qs.end(), [&](const T &q1, const T &q2) {
        auto &[l1, r1, _1] = q1;
        auto &[l2, r2, _2] = q2;
        int b1 = l1 / block_size;
        int b2 = l2 / block_size;
        return b1 < b2 || (b1 == b2 && r1 < r2);
    });
    vector<int> occ(MAX + 1, 0);
    int distinct_cnt = 0;
    auto add = [&](int i) {
        int val = a[i];
        if (occ[val]++ == 0) {
            distinct_cnt++;
        }
    };
    auto remove = [&](int i) {
        int val = a[i];
        if (--occ[val] == 0) {
            distinct_cnt--;
        }
    };

    vector<int> ans(q);

    // inclusive [mo_left, mo_right]
    int mo_left = 0, mo_right = -1;
    for (auto &[l, r, origidx]: qs) {
        while (mo_right < r) add(++mo_right);
        while (mo_right > r) remove(mo_right--);
        while (mo_left < l) remove(mo_left++);
        while (mo_left > l) add(--mo_left);
        ans[origidx] = distinct_cnt;
    }

    for (int v: ans) {
        cout << v << '\n';
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

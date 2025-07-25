#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; int64_t k;
    cin >> n >> k;
    vector<int64_t> t(n), a(n);
    for (auto &ti: t) {
        cin >> ti;
        if (ti == 2) ti = -1;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] *= t[i];
    }
    vector<int64_t> prefvals = {0};
    vector<int64_t> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
        prefvals.push_back(pref[i + 1]);
    }
    sort(prefvals.begin(), prefvals.end());
    prefvals.erase(unique(prefvals.begin(), prefvals.end()), prefvals.end());
    auto get_pref_idx = [&](int64_t val) {
        return int(lower_bound(prefvals.begin(), prefvals.end(), val) - prefvals.begin());
    };

    vector<int> prefidx(n + 1), lef(n + 1), rig(n + 1);
    for (int i = 0; i <= n; i++) {
        int64_t p = pref[i];
        int idx = get_pref_idx(p);
        prefidx[i] = idx;

        lef[i] = get_pref_idx(p - k);
        if (lef[i] >= int(prefvals.size()) || prefvals[lef[i]] != p - k) lef[i] = -1;

        rig[i] = get_pref_idx(p + k);
        if (rig[i] >= int(prefvals.size()) || prefvals[rig[i]] != p + k) rig[i] = -1;
    }

    int q;
    cin >> q;
    using Q = array<int,3>;
    vector<Q> qs(q);
    for (int i = 0; i < q; i++) {
        auto &[l, r, idx] = qs[i];
        cin >> l >> r;
        l--;r--;
        idx = i;
    }
    int block_size = int(sqrt(n));
    sort(qs.begin(), qs.end(), [&](const Q &q1, const Q &q2) {
        auto &[l1, r1, _1] = q1;
        auto &[l2, r2, _2] = q2;
        int b1 = l1 / block_size;
        int b2 = l2 / block_size;
        return b1 < b2 || (b1 == b2 && r1 < r2);
    });
    vector<int> cnt(int(prefvals.size()), 0);
    cnt[get_pref_idx(0)] = 1;
    int64_t cur_cnt = 0;
    auto add_right = [&](int i) {
        // without coord compression (just a map):
        // uses 0-indexing
        // cur_cnt += cnt[pref[i] - k];
        // cnt[pref[i]]++;

        i++;    // uses 1-indexing
        if (lef[i] != -1) {
            cur_cnt += cnt[lef[i]];
        }
        cnt[prefidx[i]]++;
    };
    auto remove_right = [&](int i) {
        // cnt[pref[i]]--;
        // cur_cnt -= cnt[pref[i] - k];
        i++;
        cnt[prefidx[i]]--;
        if (lef[i] != -1) {
            cur_cnt -= cnt[lef[i]];
        }
    };
    auto add_left = [&](int i) {
        // int64_t p = i > 0 ? pref[i - 1] : 0;
        // cur_cnt += cnt[p + k];
        // cnt[p]++;
        i++;
        if (rig[i - 1] != -1) {
            cur_cnt += cnt[rig[i - 1]];
        }
        cnt[prefidx[i - 1]]++;
    };
    auto remove_left = [&](int i) {
        // int64_t p = i > 0 ? pref[i - 1] : 0;
        // cnt[p]--;
        // cur_cnt -= cnt[p + k];
        i++;
        cnt[prefidx[i - 1]]--;
        if (rig[i - 1] != -1) {
            cur_cnt -= cnt[rig[i - 1]];
        }
    };
    vector<int64_t> ans(q);
    int mo_left = 0, mo_right = -1;
    for (auto &[l, r, origidx]: qs) {
        while (mo_right < r) add_right(++mo_right);
        while (mo_right > r) remove_right(mo_right--);
        while (mo_left < l) remove_left(mo_left++);
        while (mo_left > l) add_left(--mo_left);
        ans[origidx] = cur_cnt;
    }
    for (int64_t v: ans) {
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

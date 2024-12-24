#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<array<int,3>> upd(n);
    for (auto &x: upd) cin >> x[0] >> x[1] >> x[2];
    vector<array<int,2>> qur(q);
    for (auto &x: qur) cin >> x[0] >> x[1];

    vector<int> compressed_indices;
    for (auto &x: upd) {
        compressed_indices.push_back(x[0]);
        compressed_indices.push_back(x[1]);
    }
    for (auto &x: qur) {
        compressed_indices.push_back(x[0]);
        compressed_indices.push_back(x[1]);
    }
    sort(compressed_indices.begin(), compressed_indices.end());
    compressed_indices.erase(unique(compressed_indices.begin(), compressed_indices.end()), compressed_indices.end());
    // cout << "INDICES: ";
    // for (int idx: compressed_indices) {
    //     cout << idx << " ";
    // }
    // cout << endl;
    int size = int(compressed_indices.size());
    vector<int64_t> pref(size + 1, 0), value(size + 1, 0), diff(size + 1, 0);
    for (auto &[l, r, v]: upd) {
        int lidx = int(lower_bound(compressed_indices.begin(), compressed_indices.end(), l) - compressed_indices.begin());
        int ridx = int(lower_bound(compressed_indices.begin(), compressed_indices.end(), r) - compressed_indices.begin());
        diff[lidx + 1] += v;
        diff[ridx + 1] -= v;
    }

    for (int i = 1; i < size; i++) {
        value[i] = value[i - 1] + diff[i];
    }
    for (int i = 1; i < size; i++) {
        int l = compressed_indices[i - 1];
        int r = compressed_indices[i];
        int width = r - l;

        // pref[i + 1] = pref[i] + value[i] * width + pref[i + 1];
        pref[i] = pref[i - 1] + value[i] * width;
    }
    // for (int i = 0; i < size; i++) {
    //     cout << value[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < size; i++) {
    //     cout << pref[i] << " ";
    // }
    // cout << endl;
    for (auto &[l, r]: qur) {
        int lidx = int(lower_bound(compressed_indices.begin(), compressed_indices.end(), l) - compressed_indices.begin());
        int ridx = int(lower_bound(compressed_indices.begin(), compressed_indices.end(), r) - compressed_indices.begin());
        int64_t ans = pref[ridx] - pref[lidx];
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

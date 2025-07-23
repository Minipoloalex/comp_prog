#include <bits/stdc++.h>
using namespace std;


int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int64_t> v(n);
    for (auto &x: v) cin >> x;

    int block_size = int(ceil(sqrt(n)));
    vector<int64_t> blocks;
    auto idx_to_block = [&](int idx) {
        return idx / block_size;
    };
    auto block_to_fst_idx = [&](int blockidx) {
        return blockidx * block_size;
    };
    auto query = [&](int r) {
        int64_t ans = 0;
        int blockidx = idx_to_block(r);
        for (int b = 0; b < blockidx; b++) {
            ans += blocks[b];
        }
        int fst_index_block = block_to_fst_idx(blockidx);
        for (int i = fst_index_block; i <= r && i < n; i++) {
            ans += v[i];
        }
        return ans;
    };
    auto query_ans = [&](int l, int r) {
        int64_t lval = (l > 0 ? query(l - 1) : 0);
        return query(r) - lval;
    };
    auto update = [&](int i, int64_t val) {
        int blockidx = idx_to_block(i);
        int64_t diff = val - v[i];
        v[i] = val;
        blocks[blockidx] += diff;
    };
    auto init = [&](vector<int64_t> &arr) {
        for (int i = 0; i < n; i++) {
            int block_idx = idx_to_block(i);
            blocks[block_idx] += arr[i];
        }
    };
    int nr_blocks = idx_to_block(n - 1) + 1;
    blocks.assign(nr_blocks, 0);
    init(v);
    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1) {
            a--;
            update(a, b);
        }
        else {
            assert(type == 2);
            a--;b--;
            cout << query_ans(a, b) << '\n';
        }
    }
    return 0;
}
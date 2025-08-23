#include <bits/stdc++.h>
using namespace std;

const int MAX_NR_BITS = 30;

class BitwiseTrie {
    int n;
    vector<array<int,2>> trie;
    vector<int> mx;
    int node_cnt = 0;

    inline int get_bit(int x, int bit_pos) {
        return (x & (1 << bit_pos)) >> bit_pos;
    }

public:
    BitwiseTrie(int _n, int bit_count = 32):
        n(_n), trie(n * bit_count + 1, {0, 0}),
        mx(n * bit_count + 1, INT_MIN) {}

    void insert(int idx, int val) {
        int node = 0;
        mx[node] = max(mx[node], idx);
        for (int b = MAX_NR_BITS - 1; b >= 0; b--) {
            int bit = get_bit(val, b);
            if (trie[node][bit] == 0) {
                trie[node][bit] = ++node_cnt;
            }
            node = trie[node][bit];
            mx[node] = max(mx[node], idx);
        }
    }
    int get(int k, int val) { // specialized function for this problem
        int mx_idx = INT_MIN;
        int node = 0;
        for (int b = MAX_NR_BITS - 1; b >= 0; b--) {
            int bit = get_bit(val, b);
            int kbit = get_bit(k, b);
            if (kbit == 1) {
                // need to find the other bit, otherwise invalid
                if (trie[node][bit ^ 1] == 0) {
                    break;
                }
                node = trie[node][bit ^ 1];
            }
            else {
                assert(kbit == 0);
                if (trie[node][bit ^ 1] != 0) {
                    // valid, since it makes K large
                    mx_idx = max(mx_idx, mx[trie[node][bit ^ 1]]);
                }
                if (trie[node][bit] != 0) {
                    // not immediately valid, but may be in the future
                    node = trie[node][bit];
                }
                else {
                    // if there's nothing valid in this path, we've finished
                    break;
                }
            }
            if (b == 0) {
                // finished and we can reach K (is still valid)
                mx_idx = max(mx_idx, mx[node]);
            }
        }
        return mx_idx;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    BitwiseTrie trie(n);
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        trie.insert(i, a[i]);
        int mx_idx = trie.get(k, a[i]);
        if (mx_idx != INT_MIN) {
            ans = min(ans, i - mx_idx + 1);
        }
    }
    if (ans == INT_MAX) ans = -1;
    cout << ans << '\n';
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

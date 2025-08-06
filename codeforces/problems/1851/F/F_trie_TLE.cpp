#include <bits/stdc++.h>
using namespace std;

const int MAX = 32 * int(2e5);
int trie[MAX + 1][2];
int stop[MAX];
int node_cnt = 0;

inline int get_bit(int x, int bit_pos) {
    return (x & (1 << bit_pos)) >> bit_pos;
}

void trie_insert(int id, int x, int k) {
    int node = 0;
    for (int b = k - 1; b >= 0; b--) {
        int bit = get_bit(x, b);
        if (trie[node][bit] == 0) {
            trie[node][bit] = ++node_cnt;
        }
        node = trie[node][bit];
    }
    stop[node] = id;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    int best = 0;
    int ansi = 0, ansj = 1;
    int ansx = 0;

    trie_insert(0, a[0], k);
    for (int i = 1; i < n; i++) {
        int node = 0;
        int v = 0, curx = 0;
        for (int b = k - 1; b >= 0; b--) { // msb order (greedy choices of larger bits)
            int ai_bit = get_bit(a[i], b);
            int bit = ai_bit;
            if (trie[node][bit] == 0) {
                // bit not available
                bit ^= 1;
            }
            else {
                // bit available
                if (ai_bit == 0) {
                    curx |= (1 << b);
                }
                v |= (1 << b);
            }
            assert(trie[node][bit] != 0);

            node = trie[node][bit];
        }
        int otherid = stop[node];
        if (v > best) {
            best = v;
            ansx = curx;
            ansi = min(i, otherid);
            ansj = max(i, otherid);
        }

        trie_insert(i, a[i], k);
    }
    // cout << ((ansx ^ a[ansi]) & (ansx ^ a[ansj])) << " ";
    cout << ansi + 1 << " " << ansj + 1 << " " << ansx << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        // This obviously TLEs
        node_cnt = 0;
        memset(trie, 0, sizeof(trie));
        memset(stop, 0, sizeof(stop));
        solve();
    }
    return 0;
}

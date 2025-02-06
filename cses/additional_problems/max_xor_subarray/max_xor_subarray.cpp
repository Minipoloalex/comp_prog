#include <bits/stdc++.h>
using namespace std;

const int MAX = 32 * int(2e5);
int trie[MAX + 1][2];
bool stop[MAX];
int node_cnt = 0;

inline int get_bit(int x, int bit_pos) {
    return (x & (1 << bit_pos)) >> bit_pos;
}

void trie_insert(int x) {
    int node = 0;
    for (int b = 30; b >= 0; b--) {
        int bit = get_bit(x, b);
        if (trie[node][bit] == 0) {
            trie[node][bit] = ++node_cnt;
        }
        node = trie[node][bit];
    }
    stop[node] = true;
}

void solve() {
    int n;
    cin >> n;
    int pref = 0;
    int ans = 0;
    trie_insert(pref);
    while (n--) {
        int x;
        cin >> x;
        pref ^= x;
        int node = 0;
        int prev = 0;
        for (int b = 30; b >= 0; b--) { // msb order (greedy choices of larger bits)
            int bit = get_bit(pref, b);
            if (trie[node][bit ^ 1] != 0) {
                // best option is opposite bit
                // if it is present, we pick it
                // if not, we pick our bit (worse but what is possible)
                bit ^= 1;
            }
            assert(trie[node][bit] != 0);
            prev |= bit << b;
            node = trie[node][bit];
        }
        assert(stop[node]);

        ans = max(ans, pref ^ prev);
        trie_insert(pref);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

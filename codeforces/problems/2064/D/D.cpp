#include <bits/stdc++.h>
using namespace std;

int msb_idx(int val) {
    if (val == 0) return 0;
    return 31 - __builtin_clz(val) + 1;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];

    vector<int> prefXOR(n + 1);
    for (int i = 1; i <= n; i++) {
        prefXOR[i] = prefXOR[i-1] ^ w[i];
    }
    auto rsqXOR = [&](int i, int j) {
        if (i > j) return 0;
        return prefXOR[j] ^ prefXOR[i - 1];
    };
    array<int,32> def;
    for (int i = 0; i < 32; i++) def[i] = 0;

    vector<array<int,32>> preflast(n + 1, def);
    for (int i = 1; i <= n; i++) {
        preflast[i] = preflast[i - 1];
        int msbidx = msb_idx(w[i]);
        assert(msbidx != 0);    // w[i] >= 1
        for (int j = 0; j <= msb_idx(w[i]); j++) {
            preflast[i][j] = i;
        }
    }

    while (q--) {
        int x;
        cin >> x;
        int pos = n + 1;
        while (pos > 1) {
            int prv = pos;
            int msbX = msb_idx(x);
            int nxt = preflast[pos - 1][msbX] + 1;
            x = x ^ rsqXOR(nxt, pos - 1);
            if (nxt > 1 && x >= w[nxt - 1]) {
                x ^= w[nxt - 1];
                nxt--;
            }

            pos = nxt;
            if (pos == 0) break;
            if (nxt == prv) {
                break;
            }
        }
        pos = max(pos, 1);
        int ans = n + 1 - pos;
        cout << ans << " ";
    }
    cout << '\n';
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

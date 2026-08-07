#include <bits/stdc++.h>
using namespace std;
const int MX_AI = int(1e6);

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<string> g(n);
    for (auto &x: g) cin >> x;

    vector<int> ans(MX_AI+1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    int ci = i, cj = j;

                    // previous result (does not consider cur): added to cur to get current result
                    int64_t prv = 0;
                    // current parcel (for multiplication purposes)
                    int64_t cur = 1;
                    int64_t nr = 0; // for building numbers

                    int iters = 0;
                    bool is_nr = false;
                    while (ci >= 0 && ci < n && cj >= 0 && cj < m) {
                        bool prv_is_nr = is_nr;
                        char ch = g[ci][cj];
                        is_nr = false;

                        if (ch == '*') {
                            if (prv_is_nr) {
                                cur *= nr;
                                nr = 0;
                            }
                            else break;
                        }
                        else if (ch == '+') {
                            if (prv_is_nr) {
                                prv += cur * nr;
                                cur = 1;
                                nr = 0;
                            }
                            else break;
                        }
                        else {
                            nr *= 10;
                            is_nr = true;
                            nr += (ch - '0');
                        }

                        if (is_nr && (iters > 0 || (iters == 0 && dx == -1 && dy == -1))) {
                            // ensure not counting 8 times when it's just the number itself
                            int64_t val = prv + cur * nr;
                            if (val > MX_AI) break;
                            ans[val]++;
                        }
                        ci += dx;
                        cj += dy;
                        iters++;
                    }
                }
            }
        }
    }

    while (q--) {
        int ai;
        cin >> ai;
        cout << ans[ai] << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

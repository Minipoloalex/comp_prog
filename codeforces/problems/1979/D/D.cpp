#include <bits/stdc++.h>
using namespace std;

int get_digit(char c) {
    return c - '0';
}

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    using T = array<int,6>;
    T def = {1, 0, 0, 1, 0, 0};
    auto update = [&](int i, T &cur) {
        auto &[possible, curcnt, curdigit, first, cntfirst, digitfirst] = cur;
        int d = get_digit(s[i]);
        if (curcnt == 0) {
            curcnt = 1;
            curdigit = d;
        }
        else if (d == curdigit) {
            if (curcnt == k) {
                possible = false;
            }
            if (curcnt < k) {
                curcnt++;
            }
        }
        else {
            assert(d != curdigit);
            if (curcnt != k) {
                if (first) {
                    curcnt = 1;
                    curdigit = d;
                    first = false;
                }
                else {
                    possible = false;
                }
            }
            else {
                if (first) {
                    first = false;
                }
                curdigit = d;
                curcnt = 1;
            }
        }
        if (first) {
            cntfirst = curcnt;
            digitfirst = curdigit;
        }
    };
    vector<T> suf(n + 1);
    // [possible, curcnt, curdigit, first, cntfirst, digitfirst]
    suf[n] = def;
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1];
        update(i, suf[i]);
    }
    int ans = -1;
    T pref = def;
    for (int i = 0; i < n; i++) {
        update(i, pref);
        auto [prefpossible, prefcnt, prefdigit, preffirst, prefcntfirst, prefdigitfirst] = pref;
        auto [sufpossible, sufcnt, sufdigit, suffirst, sufcntfirst, sufdigitfirst] = suf[i + 1];
        if (i == n - 1) {
            if (prefpossible && prefcnt == k) {
                // cout << i + 1 << " ";
                ans = i + 1;
            }
        }
        else {
            if (sufpossible && prefpossible) {
                if ((
                        (sufcntfirst == k && prefcnt == k && sufdigitfirst != prefdigit) ||
                        (sufdigitfirst == prefdigit && sufcntfirst + prefcnt == k)
                    )
                    &&
                    (
                        sufcnt == k || suffirst
                    )
                ) {
                    // cout << i + 1 << " ";
                    ans = i + 1;
                }
            }
        }
    }

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

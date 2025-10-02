#include <bits/stdc++.h>
using namespace std;

int64_t sos[1 << 20];

void solve() {
    int n, k;
    cin >> n >> k;
    auto read_skills = [&]() {
        string s;
        cin >> s;
        int skills = 0;
        for (int j = 0; j < k; j++) {
            if (s[j] == '1') {
                skills |= (1 << j);
            }
        }
        return skills;
    };
    for (int i = 0; i < n; i++) {
        sos[read_skills()]++;
    }
    for (int i = 0; i < k; i++) {
        for (int mask = 0; mask < (1 << k); mask++) {
            if (mask & (1 << i)) {
                // include all subsets (union will never exceed the specific mask)
                sos[mask] += sos[mask ^ (1 << i)];
            }
        }
    }
    auto choose3 = [](int64_t NR) -> int64_t {
        if (NR < 3) return 0;
        return NR * (NR - 1) * (NR - 2) / 6;
    };
    for (int i = 0; i < (1 << k); i++) {
        sos[i] = choose3(sos[i]);
    }
    for (int i = 0; i < k; i++) {
        for (int mask = 0; mask < (1 << k); mask++) {
            if (mask & (1 << i)) {
                // exclude (strict) subsets (union does not equal the specific mask)
                sos[mask] -= sos[mask ^ (1 << i)];
            }
        }
    }
    int m;
    cin >> m;
    while (m--) {
        cout << sos[read_skills()] << '\n';
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

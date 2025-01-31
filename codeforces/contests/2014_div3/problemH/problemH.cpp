#include <bits/stdc++.h>
using namespace std;

using usi = unordered_set<int64_t>;
using umii = unordered_map<int64_t, int64_t>;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t;
    cin >> t;
    random_device rd;
    mt19937_64 gen(rd());
    while (t--) {
        int n, q;
        cin >> n >> q;
        // vector<int64_t> pref(n + 1);
        vector<int64_t> hsh_pref(n + 1);
        umii hsh;
        usi rnd = {0};

        // pref[0] = 0;
        hsh_pref[0] = 0;
        int64_t tmp;
        for (int i = 1; i <= n; i++) {
            int64_t ai; cin >> ai;
            // pref[i] = pref[i - 1] ^ ai;

            int64_t rnd_val;
            if (!hsh.contains(ai)) {
                do {
                    tmp = gen();
                } while (rnd.contains(tmp));

                hsh[ai] = tmp;
                rnd.insert(tmp);
                rnd_val = tmp;
            }
            else rnd_val = hsh[ai];

            hsh_pref[i] = hsh_pref[i - 1] ^ rnd_val;
        }
        while (q--) {
            int l, r;
            cin >> l >> r;
            // if ((pref[r] ^ pref[l - 1]) == 0 && (hsh_pref[r] ^ hsh_pref[l - 1]) == 0) cout << "YES\n";
            if ((hsh_pref[r] ^ hsh_pref[l - 1]) == 0) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}

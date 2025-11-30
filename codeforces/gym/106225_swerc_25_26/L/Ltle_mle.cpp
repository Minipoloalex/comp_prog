#include <bits/stdc++.h>
using namespace std;

/**
 * Usage:
 *  string s; str_hash<2> H(s); 
 * auto hashed = H.get_hash(0, n-1);
 */
template <int H>
struct str_hash {
    static constexpr uint64_t m = 4294953959; // 1000000009 or 4294953959
    static constexpr int n_hashes = H;
    int n; // size of string
    // h[i][j] = hash of first j chars with base b[i] (1-indexed positions)
    // p[i][j] = b[i]^j % m 
    vector<vector<uint64_t>> h, p;
    array<uint64_t, n_hashes> b; // bases, randomized per instance

    str_hash(const string& s) : // s: string to hash
        n(int(s.size())),
        h(n_hashes, vector<uint64_t>(n + 1, 0)),
        p(n_hashes, vector<uint64_t>(n + 1, 1)) {
        static thread_local // avoids same base in same clock tick
            mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
        for (auto& base : b) base = uniform_int_distribution<uint64_t>(2, m - 2)(rng);

        for (int i = 0; i < n_hashes; i++) {
        for (int j = 1; j <= n; j++) {
            h[i][j] = (h[i][j - 1] * b[i] % m + s[j - 1]) % m;
            p[i][j] = p[i][j - 1] * b[i] % m;
        }
        }
    }

    // l and r are 0 indexed
    uint64_t get_hash(int l, int r) const {
        array<uint64_t, n_hashes> res;
        for (int i = 0; i < n_hashes; i++) {
        res[i] = h[i][r + 1] - h[i][l] * p[i][r - l + 1] % m;
        res[i] = (res[i] + m) % m;
        } return res[0] | uint64_t(res[1] << 32);
    }
};
typedef uint64_t HASH;

#include <bits/extc++.h>

// smallest exponent of 2 greater than 26*5e5
__gnu_pbds::gp_hash_table<HASH,vector<int>> mp({},{},{},{},{1<<24});
const int MAXN = int(5e5);

// HASH hashes[26*MAXN];
// vector<int> occ[26*MAXN];

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    str_hash<2> hsh(s);

    // coord compression solution:
    // int sz = 0;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < 26 && i+j < n; j++) {
    //         hashes[sz++] = hsh.get_hash(i,i+j);
    //     }
    // }
    // sort(hashes, hashes + sz);
    // auto get_idx = [&](HASH const& myhash) {
    //     return int(lower_bound(hashes, hashes + sz, myhash) - hashes);
    // };
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < 26 && i+j < n; j++) {
    //         auto myhash = hsh.get_hash(i,i+j);
    //         int idx = get_idx(myhash);
    //         occ[idx].push_back(i);
    //     }
    // }

    // unordered map solution:
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26 && i+j < n; j++) {
            auto myhash = hsh.get_hash(i,i+j);
            mp[myhash].push_back(i);
        }
    }
    // vector<array<int,26>> pref(n+1, array<int,26>{});
    // for (int i = 0; i < n; i++) {
    //     pref[i+1] = pref[i];
    //     pref[i+1][s[i] - 'a']++;
    // }
    // vector<array<int,26>> lst(n+1, array<int,26>{});
    // for (int i = 0; i < n; i++) {
    //     lst[i+1]=lst[i];
    //     lst[i+1][s[i]-'a']=i+1;
    // }
    vector<vector<int>> chocc(26);
    for (int i = 0; i < n; i++) {
        chocc[s[i]-'a'].push_back(i);
    }
    array<int,26> freq;
    while (q--) {
        int l, r;
        cin >> l >> r;
        int mx = 0;
        for (int i = 0; i < 26; i++) {
            freq[i] = int(
                upper_bound(chocc[i].begin(), chocc[i].end(), r-1) -
                lower_bound(chocc[i].begin(), chocc[i].end(), l-1)
            );
            mx = max(mx, freq[i]);
        }
        vector<int> most;
        for (int i = 0; i < 26; i++) {
            if (freq[i] == mx) {
                most.push_back(i);
            }
        }
        // array<int,26> freq{};
        // for (int i = 0; i < 26; i++) {
        //     freq[i] = pref[r][i]-pref[l-1][i];
        //     mx = max(mx, freq[i]);
        // }
        // vector<int> most;
        // for (int i = 0; i < 26; i++) {
        //     if (freq[i] == mx) {
        //         most.push_back(i);
        //     }
        // }
        int ans = 1;
        // for (int c = 0; c < 26; c++) {
        for (int c: most) {
            // using the last occurrence is easier (e.g. 3rd query, test case 1)

            // int st = lst[r][c]; // 1-indexed
            int st = *prev(upper_bound(chocc[c].begin(), chocc[c].end(), r-1))+1; // 1-indexed

            for (int j = ans; j < 26 && st + j <= r; j++) {
                auto myhash = hsh.get_hash(st-1,st+j-1);    // 1-indexed to 0-index
                // unordered map
                vector<int> &myocc = mp[myhash];

                // coord compr
                // int idx = get_idx(myhash);
                // int cnt = int(
                //     upper_bound(occ[idx].begin(), occ[idx].end(), r-1) -
                //     lower_bound(occ[idx].begin(), occ[idx].end(), l-1)
                // );
                int cnt = int(
                    upper_bound(myocc.begin(), myocc.end(), r-1) -
                    lower_bound(myocc.begin(), myocc.end(), l-1)
                );

                if (cnt == mx) {
                    ans = j+1;
                }
                else break;
            }
        }
        cout << ans << '\n';
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

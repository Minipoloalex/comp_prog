#include <bits/stdc++.h>
using namespace std;

/*
Definitions:
 A border of a string is a (proper) prefix that is also a suffix of the string (but not the whole string).
 For example, the borders of "defdedefde" are "de" and "defde".
 KMP[i + 1]: contains the length of the longest border of the prefix of P that ends at i.
 Example: "abacababc": kmp = [-1, 0, 0, 1, 0, 1, 2, 3, 2, 0]

 Don't confuse the prefix from the border definition with this other prefix.
 Here, the prefix that ends at i takes the role of the whole string in the border definition.
*/

/*
Returns: Pattern preprocessed (back jumps): [-1, 0, ...]
(-1 is only used to simplify implementation) 
Time: O(|p|)
*/
vector<int> kmpPreprocess(const string &p) { // pattern p
    int sz = int(p.size());
    vector<int> kmp(sz + 1);

    int l = -1, r = 0;
    kmp[0] = -1;
    while (r < sz) {    // l < r
        while (l >= 0 && p[r] != p[l]) l = kmp[l];
        l++; r++;

        // Here, we have l >= 0 and r >= 1
        // Comparison of the i'th character corresponds to
        // the (i + 1)'th position in the array
        kmp[r] = l;
    }
    return kmp;
}

/*
Given preprocessed p (and corresponding pi/kmp array), searches for its occurrences in t
Time: O(|t|)
Alternatively, use pi(<pattern>#<text>) and look for sz(pattern) in pi array
*/
void kmpSearch(const string &p, const string &t, const vector<int> &kmp) {
    int n = int(t.size());
    int m = int(p.size());
    int i = 0, j = 0;   // i loops through text, j through pattern
    while (i < n) {
        while (j >= 0 && (t[i] != p[j])) j = kmp[j];
        i++; j++;
        if (j == m) {
            cout << "Match found starting at index " << i - j << '\n';
            j = kmp[j];  // continue looking for more matches 
        }
    }
}


typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;


void solve() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto &si: s) cin >> si;
    string p;
    cin >> p;
    vi kmp = kmpPreprocess(p);
    int m = int(p.size());

    vector<vector<pair<int,int>>> proc(n, vector<pair<int,int>>(m, {0,0}));
    for (int i = 0; i < n; i++) {
        for (int st = 0; st < m; st++) {
            int sid = 0, j = st;   // sid loops through text s[i], j through pattern
            int c = 0;
            int sz = int(s[i].size());
            while (sid < sz) {
                while (j >= 0 && (s[i][sid] != p[j])) j = kmp[j];
                sid++; j++;
                if (j == m) {
                    c++;
                    j = kmp[j];
                }
            }
            proc[i][st] = {c, j};
        }
    }

    vvvi dp(1 << n, vvi(m, vi(m, INT_MIN)));
    for (int st = 0; st < m; st++) {
        // having processed nothing, it's possible to end up at the same state as the original one
        dp[0][st][st] = 0;
    }
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int st = 0; st < m; st++) {
            for (int send = 0; send < m; send++) {
                for (int i = 0; i < n; i++) {
                    if ((mask & (1 << i))) { // can use it
                        auto [c, snew] = proc[i][st];
                        dp[mask][st][send] = max(dp[mask][st][send], dp[mask ^ (1 << i)][snew][send] + c);
                    }
                }
            }
        }
    }

    int complete_mask = (1 << n) - 1;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int sz = int(s[i].size());
        for (int mid = 0; mid <= sz; mid++) {
            // mid: nr of chars of the prefix of i that are on the suffix of the string

            int sid = mid, j = 0, cp = 0;
            while (sid < sz) { // process the suffix of i: [mid, sz), the prefix of T
                while (j >= 0 && (s[i][sid] != p[j])) j = kmp[j];
                sid++; j++;
                if (j == m) {
                    cp++;
                    j = kmp[j];
                }
            }

            for (int send = 0; send < m; send++) {
                sid = 0;    // process the prefix of i: [0, mid)
                int st = send, cs = 0;
                while (sid < mid) {
                    while (st >= 0 && (s[i][sid] != p[st])) st = kmp[st];
                    sid++; st++;
                    if (st == m) {
                        cs++;
                        st = kmp[st];
                    }
                }
                ans = max(ans, cp + dp[complete_mask ^ (1 << i)][j][send] + cs);
            }
        }
    }
    cout << ans << '\n';
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

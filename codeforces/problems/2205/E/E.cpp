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

const int MX_N = 8000;
vector<int> kmp;

/*
Returns: Pattern preprocessed (back jumps): [-1, 0, ...]
(-1 is only used to simplify implementation) 
Time: O(|p|)
*/
void kmpPreprocess(const vector<int> &p) { // pattern p
    int sz = int(p.size());
    kmp.clear();
    kmp.resize(sz+1);

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
}

const int64_t MOD = 998244353;

void solve() {
    int n;
    cin >> n;
    vector<int> T(n);
    for (auto &x: T) cin >> x;
    vector<int64_t> dp(n+1);
    dp[0] = 1;
    vector<int> aux; aux.reserve(n+1);
    for (int i = 0; i < n; i++) {
        aux.clear();
        for (int j = i; j >= 0; j--) {
            aux.push_back(T[j]);
        }
        kmpPreprocess(aux);
        for (int j = 0; j <= i; j++) {
            int idx = i - j;
            if (kmp[idx+1] <= 0) { // subarray cannot have a border
                dp[i+1] += dp[j]; // if valid
            }
        }
        dp[i+1] %= MOD;
    }
    cout << dp[n] % MOD << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    kmp.reserve(MX_N+1);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

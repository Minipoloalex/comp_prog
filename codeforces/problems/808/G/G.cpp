#include <bits/stdc++.h>
using namespace std;


/*
Definitions:
 A border of a string is a prefix that is also a suffix of the string (but not the whole string).
 For example, the borders of "defdedefde" and "de" and "defde".
 KMP[i + 1]: contains the length of the longest border of the prefix of P that ends at i.
 Example: "abacababc": kmp = [-1, 0, 0, 1, 0, 1, 2, 3, 2, 0]

 Don't confuse the prefix from the border definition with this other prefix.
 Here, the prefix that ends at i takes the role of the whole string in the border definition.
*/

// Preprocesses the pattern to match
struct KMP {
    string p;   // pattern
    int m;      // size of pattern

    // Pattern preprocessed (back jumps): [-1, 0, ...]
    // (-1 is only used to simplify build implementation)
    vector<int> pi;

    KMP(const string &pattern): p(pattern), m(int(p.size())) {
        build();
    }

    // aka kmp preprocess (pattern)
    // O(|p|)
    void build() {
        pi.resize(m + 1);
        int l = -1, r = 0;
        pi[0] = -1;
        while (r < m) {    // l < r
            while (l >= 0 && p[r] != p[l]) l = pi[l];
            l++; r++;

            // Here, we have l >= 0 and r >= 1
            // Comparison of the i'th character corresponds to
            // the (i + 1)'th position in the array
            pi[r] = l;
        }
    }
};

void solve() {
    string s, t;
    cin >> s >> t;
    int n = int(s.size());
    int m = int(t.size());
    if (m > n) {
        cout << "0\n";
        return;
    }
    KMP kmp(t);

    // This was M^2 (because it's possible for this problem)
    // However, there's a better solution:
    // https://cp-algorithms.com/string/prefix-function.html#building-an-automaton-according-to-the-prefix-function
    vector<array<int,26>> nxt(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 26; j++) {
            // i is the value of the prefix function, j is the char to handle
            // the objective is to know what will be the value of prefix function after using char j
            int l = i;
            char ch = char(j + 'a');
            while (l >= 0 && ch != t[l]) l = kmp.pi[l];
            l++;
            nxt[i][j] = l;
            // cout << nxt[i][j] << " ";
        }
        // cout << endl;
    }

    // The difference to my previous implementation (of the editorial solution, which is this one)
    // Is that this solution preprocesses nxt array and tests every possible char for '?'
    // My previous solution tried all possible kmp values for a given current index
    // That only makes sense for characters '?', and we should also preprocess the nxt array to be fast
    // For a given character though, we should also use the preprocessed (otherwise, we would have to do a loop)
    vector<vector<int>> dp(n, vector<int>(m, -1));
    function<int(int,int)> go = [&](int i, int j) {
        // here, i is the index in s, and j is the value of the prefix function
        // we can also see j as the index of the character we're trying to match from t
        if (i == n) return 0;

        int &mem = dp[i][j];
        if (mem != -1) return mem;

        int ans = 0;
        if (s[i] == '?') {
            for (int k = 0; k < 26; k++) { // try char k
                int score = 0;
                int nx = nxt[j][k];
                if (nx == m) {
                    score = 1;
                    nx = kmp.pi[nx];
                }
                ans = max(ans, score + go(i + 1, nx));
            }
        }
        else {
            int score = 0;
            int nx = nxt[j][s[i]-'a'];
            if (nx == m) {
                score = 1;
                nx = kmp.pi[nx];
            }
            ans = max(ans, score + go(i + 1, nx));
        }
        return mem = ans;
    };
    int ans = go(0, 0);
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

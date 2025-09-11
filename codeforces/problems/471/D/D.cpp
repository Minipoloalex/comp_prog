#include <bits/stdc++.h>
using namespace std;

/*
Definitions:
 A border of a string is a (proper) prefix that is also a suffix of the string (but not the whole string).
 For example, the borders of "defdedefde" and "de" and "defde".
 KMP[i + 1]: contains the length of the longest border of the prefix of P that ends at i.
 Example: "abacababc": kmp = [-1, 0, 0, 1, 0, 1, 2, 3, 2, 0]

 Don't confuse the prefix from the border definition with this other prefix.
 Here, the prefix that ends at i takes the role of the whole string in the border definition.
*/

// Preprocesses the pattern to match
struct KMP {
    vector<int> p;   // pattern
    int m;      // size of pattern

    // Pattern preprocessed (back jumps): [-1, 0, ...]
    // (-1 is only used to simplify build implementation)
    vector<int> pi;

    KMP(const vector<int> &pattern): p(pattern), m(int(p.size())) {
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

    // Given preprocessed p, searches for its occurrences in t
    // Time: O(|t|)
    // Alternatively, use pi(<pattern>#<text>) and look for sz(pattern) in pi array
    int match(const vector<int> &t) {
        int ans = 0;
        int n = int(t.size());
        int i = 0, j = 0;   // i loops through text, j through pattern
        while (i < n) {
            while (j >= 0 && (t[i] != p[j])) j = pi[j];
            i++; j++;
            if (j == m) {
                // cout << "Match found starting at index " << i - j << '\n';
                ans++;
                j = pi[j];  // continue looking for more matches 
            }
        }
        return ans;
    }
};

void solve() {
    int n, w;
    cin >> n >> w;
    vector<int> a(n), b(w);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    if (w == 1) {
        cout << n << '\n';
        return;
    }
    vector<int> p, t;
    for (int i = 1; i < w; i++) {
        p.push_back(b[i] - b[i - 1]);
    }
    for (int i = 1; i < n; i++) {
        t.push_back(a[i] - a[i - 1]);   
    }
    KMP kmp(p);
    int ans = kmp.match(t);
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

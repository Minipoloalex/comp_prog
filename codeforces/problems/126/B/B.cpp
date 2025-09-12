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

// Preprocesses the pattern
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
    // Given preprocessed p, searches for its occurrences in t
    // Time: O(|t|)
    // Alternatively, use pi(<pattern>#<text>) and look for sz(pattern) in pi array
    void match(const string &t) {
        int n = int(t.size());
        int i = 0, j = 0;   // i loops through text, j through pattern
        while (i < n) {
            while (j >= 0 && (t[i] != p[j])) j = pi[j];
            i++; j++;
            if (j == m) {
                cout << "Match found starting at index " << i - j << '\n';
                j = pi[j];  // continue looking for more matches 
            }
        }
    }
};

//  z[i] is the LCP (longest common prefix) of s and s.substr(i) (suffix of S starting at i: s[i:]).
// For S = "aabxaayaab", Z = [10, 1, 0, 0, 2, 1, 0, 3, 1, 0] (same size as S)
vector<int> z_function(const string &s) {
	vector<int> z(s.size());
	z[0] = (int) s.size();

	int l = 0, r = 0;
	for (int i = 1; i < (int) s.size(); i++) {
		z[i] = max(0, min(z[i - l], r - i + 1));
		while (i + z[i] < (int) s.size() && s[z[i]] == s[i + z[i]]) {
			l = i;
			r = i + z[i];
			z[i]++;
		}
	}
	return z;
}


int solve_kmp(int n, string s) {
    KMP kmp(s);
    int mx = 0;
    for (int i = 2; i < n; i++) {
        mx = max(mx, kmp.pi[i]);    // don't include suffix (index n)
    }
    int j = n;
    while (kmp.pi[j] > 0 && kmp.pi[j] > mx) {
        j = kmp.pi[j];
    }
    return min(kmp.pi[j], mx);
}

int solve_z(int n, string s) {
    vector<int> z = z_function(s);
    int mx_middle = 0;
    vector<bool> validsfx(n);   // similar idea to the above (KMP)
    for (int i = 1; i < n; i++) {
        if (i + z[i] == n) {
            validsfx[z[i]] = 1;
            mx_middle = max(mx_middle, z[i] - 1);
        }
        else {
            mx_middle = max(mx_middle, z[i]);
        }
    }
    // middle can adapt as it wants, the suffix can't
    // can't make suffix smaller, unless it's valid
    for (int i = mx_middle; i >= 0; i--) {
        if (validsfx[i]) return i;
    }
    return 0;
}

void solve() {
    string s;
    cin >> s;
    int n = int(s.size());
    int sz = solve_z(n, s);
    assert(sz == solve_kmp(n, s));

    string ans = s.substr(0, sz);
    if (ans.empty()) {
        ans = "Just a legend";
    }
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

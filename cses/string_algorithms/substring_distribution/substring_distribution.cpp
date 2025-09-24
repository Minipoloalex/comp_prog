#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

#define sz(v) int((v).size())
#define all(v) (v).begin(), (v).end()

// Adapted from KACTL
/*
 * Builds suffix array for a string.
 * sa[i] is the starting index of the suffix which
 * is i'th in the sorted suffix array.
 * The returned vector is of size n+1, and sa[0] = n.
 * The lcp array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * lcp[i] = lcp(sa[i], sa[i-1]), lcp[0] = 0.
 * The input string must not contain any nul chars.
 * Always ensure the last character is the smallest,
 * especially when working with multiple strings (e.g. LCS).
 * Time: O(n log n)
 */
struct SuffixArray {
	vi sa, lcp;
    string s;   // or vector<int>
    int lim;
    SuffixArray(string _s, int _lim=256): s(_s), lim(_lim) {
        s.push_back(0);
        init();
    }
    void init() {
        int n = sz(s), k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			for (int i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			for (int i = 0; i < n; i++) ws[x[i]]++;
			for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			for (int i = 1; i < n; i++) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
    }
    vector<int> substring_distribution() {
        int n = sz(s);
        vector<int> d(n);
        for (int i = 1; i < n; i++) {
            int SZ = n - 1 - sa[i]; // [sa[i], n-1)
            int mn_sz = lcp[i] + 1;
            int mx_sz = SZ;
            if (mn_sz < n) {
                d[mn_sz]++;
            }
            if (mx_sz + 1 < n) {
                d[mx_sz + 1]--;
            }
        }
        for (int i = 1; i < n; i++) {
            d[i] += d[i - 1];
        }
        return d;
    }
};

void solve() {
    string s;
    cin >> s;
    SuffixArray sa(s);
    vector<int> ans = sa.substring_distribution();
    for (int i = 1; i < sz(ans); i++) {
        cout << ans[i] << " \n"[i == sz(ans) - 1];
    }
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

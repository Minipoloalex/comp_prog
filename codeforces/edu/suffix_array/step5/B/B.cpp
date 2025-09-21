#include <bits/stdc++.h>
using namespace std;

/*
 * From KACTL
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

typedef vector<int> vi;

#define sz(v) int((v).size())
#define all(v) (v).begin(), (v).end()

struct SuffixArray {
	vi sa, lcp;
    int sz_fst;
    string s;   // or vector<int>
    int lim;
    SuffixArray(string _s, string _t, int _lim=256) {
        sz_fst = sz(_s);
        s = _s;
        s.push_back(1);
        s += _t;
        s.push_back(0);
        lim = _lim;
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

        // vi isa(sa.size());
        // for (int i = 0; i < (int)sa.size(); ++i) isa[sa[i]] = i;
    }
    pair<int,int> lcs() {
        int n = sz(s);
        int mx = 0, lcp_idx = 0;
        for (int i = 1; i < n; i++) {
            bool dif_strs = (sa[i-1] < sz_fst) != (sa[i] < sz_fst);
            if (dif_strs && lcp[i] > mx) {
                mx = lcp[i];
                lcp_idx = i;
            }
        }
        return {mx, lcp_idx};
    }
    // int getLCP(int a, int b) {
    //     if (a==b) return sz(s)-a; 
    //     int i = isa[a], j = isa[b]; if (i>j) swap(i,j);
    //     return rmq.query(i+1, j); // lcp is between neighbors
    // }
};

void solve() {
    string s, t;
    cin >> s >> t;
    SuffixArray sa(s, t);
    auto [lcs_sz, lcp_idx] = sa.lcs();
    cout << sa.s.substr(sa.sa[lcp_idx], lcs_sz) << '\n';
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

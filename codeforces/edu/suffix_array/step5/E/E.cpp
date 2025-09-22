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
    vector<int> s;   // or vector<int>
    int lim;
    SuffixArray(vector<int> _s, int _lim=256): s(_s), lim(_lim) {
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
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    SuffixArray sa(a, m + 1);
    vector<int> &lcp = sa.lcp;

    int SZ = sz(sa.s);
    vector<int> nxt(SZ), prv(SZ);   // nxt and prv smaller
    // for (int i = 0; i < SZ; i++) {
    //     cout << sa.sa[i] << " " << lcp[i] << endl;
    // }

    stack<int> s;
    for (int i = 0; i < SZ; i++) {
        while (!s.empty() && lcp[i] <= lcp[s.top()]) {
            s.pop();
        }
        prv[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }
    while (!s.empty()) s.pop();
    for (int i = SZ - 1; i >= 0; i--) {
        while (!s.empty() && lcp[i] <= lcp[s.top()]) {
            s.pop();
        }
        nxt[i] = s.empty() ? SZ : s.top();
        s.push(i);
    }

    pair<int64_t, pair<int,int>> ans = {n, {0, n}};  // case of no substring being repeated
    for (int i = 0; i < SZ; i++) {
        int occ = nxt[i] - prv[i];
        int64_t refrain = 1LL * occ * lcp[i];
        ans = max(ans, {refrain, {sa.sa[i], lcp[i]}});
    }

    auto &[start, len] = ans.second;

    cout << ans.first << '\n';
    cout << len << '\n';
    for (int i = start; i < start + len; i++) {
        cout << a[i] << " ";
    }
    cout << '\n';
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

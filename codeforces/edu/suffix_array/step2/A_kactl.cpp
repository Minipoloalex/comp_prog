#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

#define sz(v) int((v).size())
#define all(v) (v).begin(), (v).end()

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

        // vi isa(sa.size());
        // for (int i = 0; i < (int)sa.size(); ++i) isa[sa[i]] = i;
    }
    // int getLCP(int a, int b) {
    //     if (a==b) return sz(s)-a; 
    //     int i = isa[a], j = isa[b]; if (i>j) swap(i,j);
    //     return rmq.query(i+1, j); // lcp is between neighbors
    // }
};

void solve() {
    string s;
    cin >> s;
    SuffixArray sa(s);
    for (int idx: sa.sa) cout << idx << " ";
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

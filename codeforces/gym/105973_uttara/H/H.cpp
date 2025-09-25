#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

#define all(v) (v).begin(), (v).end()
#define sz(v) int((v).size())

/**
 * Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in O(1).
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: O(|V|log|V| + Q)
 */
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
    RMQ() {}
	RMQ(const vector<T> &V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			for (int j = 0; j < sz(jmp[k]); j++)
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) { // end-exclusive: [a, b)
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

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
 * isa (inverse SA) and RMQ are usually not necessary.
 * Time: O(n log n)
 */
struct SuffixArray {
	vi sa, lcp, isa;
    string s;   // or vector<int>
    int fst_sz, snd_sz;
    int lim;
    RMQ<int> rmq;
    SuffixArray(string _s, string _t, int _lim=256): s(_s), lim(_lim) {
        s = _s;
        s.push_back(1);
        s += _t;
        s.push_back(0);
        fst_sz = sz(_s);
        snd_sz = sz(_t);
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
		
		isa = vi(sa.size());
        for (int i = 0; i < sz(sa); ++i) isa[sa[i]] = i;
        rmq = RMQ(lcp);
    }
    int getLCP(int a, int b) {
        if (a == b) return sz(s) - a;
        int i = isa[a], j = isa[b];
        if (i > j) swap(i, j);
        // i + 1: lcp[i] = lcp(sa[i], sa[i-1])
        // j + 1: RMQ is end-exclusive
        return rmq.query(i + 1, j + 1);
    }
    vector<int> get_b_suffix_lcp() {
        vector<int> bLcp(snd_sz);
        int n = sz(s);
        vector<int> indsA;
        for (int i = 0; i < n; i++) {
            if (sa[i] < fst_sz) {
                indsA.push_back(i);
            }
        }
        for (int i = 0; i < n; i++) {
            if (sa[i] > fst_sz && sa[i] < n - 1) {
                // found an index of a suffix from b
                // look for closest indices from a
                // either next or previous will have the max LCP with this one
                auto ub = upper_bound(all(indsA), i);
                int mx = INT_MIN;
                if (ub != indsA.end()) {
                    mx = max(mx, getLCP(sa[i], sa[*ub]));
                }
                if (ub != indsA.begin()) {
                    mx = max(mx, getLCP(sa[i], sa[*prev(ub)]));
                }
                bLcp[sa[i] - (fst_sz + 1)] = mx;
            }
        }
        return bLcp;
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    string a, b;
    cin >> a >> b;

    SuffixArray sa(a, b);
    vector<int> bLcp = sa.get_b_suffix_lcp();
    RMQ rmq(bLcp);
    auto possible = [&](int k, int l, int r) {
        // [l, r - k + 1]
        int mn = rmq.query(l, r - k + 2);   // avoid k = 0
        return mn >= k;
    };
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;r--;
        int lo = 1, hi = r - l + 1;
        while (lo < hi) {
            int med = lo + (hi - lo + 1) / 2;
            if (possible(med, l, r)) {
                lo = med;
            }
            else {
                hi = med - 1;
            }
        }
        if (!possible(lo, l, r)) lo = 0;
        cout << lo << '\n';
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

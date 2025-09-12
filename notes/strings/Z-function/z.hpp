#include <bits/stdc++.h>
using namespace std;

// z[i] is the LCP (longest common prefix) of s and s.substr(i) (suffix of S starting at i: s[i:]).
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
#include <bits/stdc++.h>
using namespace std;

// z[i] is the LCP (longest common prefix) of s and s.substr(i) (suffix of S starting at i: s[i:]).
// For "aabxaayaab", Z = [10, 1, 0, 0, 2, 1, 0, 3, 1, 0]
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

void solve() {
    string s;
    cin >> s;
    vector<int> z = z_function(s);
    int n = int(s.size());
    vector<int> ans;
    for (int i = 1; i < n; i++) {
        if (i + z[i] == n) {
            ans.push_back(i);
        }
    }
    ans.push_back(n);
    for (int a: ans) {
        cout << a << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

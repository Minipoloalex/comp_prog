#include <bits/stdc++.h>
using namespace std;

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
    string t, p;
    cin >> t >> p;
    string together = p + '#' + t;
    vector<int> z = z_function(together);
    int ans = 0;
    for (int i = 0; i < int(z.size()); i++) {
        // cout << i << " " << z[i] << '\n';
        if (z[i] == int(p.size())) {
            // cout << "Match found at index " << i << " of together\n";
            // cout << "Match found at index " << i - int(p.size()) - 1 << " of text\n";
            ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}


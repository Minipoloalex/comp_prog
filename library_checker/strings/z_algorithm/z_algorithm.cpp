#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string &s) {
	vector<int> z(s.size());
	z[0] = s.size();

	int l = 0, r = 0;
	for (int i = 1; i < s.size(); i++) {
		z[i] = max(0, min(z[i - l], r - i + 1));
		while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
			l = i;
			r = i + z[i];
			z[i]++;
		}
	}
	return z;
}

void solve() {
    string S;
    cin >> S;
    vector<int> z = z_function(S);
    for (int zi: z) {
        cout << zi << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();    
    return 0;
}

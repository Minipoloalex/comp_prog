#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    string pref = "aA0?";
    vector<char> symbols(8);
    iota(symbols.begin(), symbols.end(), '!');

    for (int i = 0; i < n; i++) {
        cout << pref;
        for (char c : symbols) cout << c;
        cout << '\n';
        next_permutation(symbols.begin(), symbols.end());
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

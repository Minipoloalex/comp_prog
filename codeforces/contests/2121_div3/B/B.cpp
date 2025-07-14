#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> f(26, 0);
    for (int i = 0; i < n; i++) {
        int idx = s[i] - 'a';
        f[idx]++;
    }
    char fst = s[0];
    char lst = s[n - 1];
    bool ans = false;
    for (int i = 0; i < 26; i++) {
        if (f[i] >= 3 || (f[i] == 2 && (fst != lst || i != (fst - 'a')))) {
            ans = true;
        }
    }
    cout << (ans ? "Yes" : "No") << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

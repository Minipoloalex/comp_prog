#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n; cin.ignore();
    vector<string> names(n);
    
    for (auto& s : names) getline(cin, s);

    auto cmp = [] (const string& a, const string& b) -> bool {
        int ai = 0, bi = 0;
        for (; !(a[ai] >= 'A' && a[ai] <= 'Z'); ai++);
        for (; !(b[bi] >= 'A' && b[bi] <= 'Z'); bi++);

        string sa = a.substr(ai), sb = b.substr(bi);
        return sa < sb;
    };

    sort(names.begin(), names.end(), cmp);
    for (auto& s : names) cout << s << endl;
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

#include <bits/stdc++.h>
using namespace std;

void transf(string &a) {
    while (true) {
        bool modif = false;
        int n = int(a.size());
        for (int i = 1; i < n; i++) {
            if (a[i] == a[i - 1]) {
                a.erase(a.begin() + i - 1, a.begin() + i + 1);
                modif = true;
                break;
            }
        }
        if (!modif) {
            return;
        }
    }
}

void solve() {
    string u, v;
    cin >> u >> v;
    bool ans = true;
    vector<int> frequ(3), freqv(3);
    int n = int(u.size()), m = int(v.size());
    for (int i = 0; i < n; i++) {
        frequ[u[i] - 'A']++;
    }
    for (int i = 0; i < m; i++) {
        freqv[v[i] - 'A']++;
    }

    for (int i = 0; i < 3; i++) {
        if (frequ[i] % 2 != freqv[i] % 2) {
            ans = false;
        }
    }
    if (ans) {
        string s, t;
        for (char c: u) {
            if (c != 'B') {
                s += c;
            }
        }
        for (char c: v) {
            if (c != 'B') {
                t += c;
            }
        }
        transf(s);
        transf(t);
        ans = s == t;
    }
    cout << (ans ? "YES": "NO") << '\n';
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

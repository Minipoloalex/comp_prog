#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << "1\n";
    }
    else {
        int cnt = (n - 3) / 2;
        vector<string> cur = {"169", "196", "961"};
        for (int i = 0; i < cnt; i++) {
            vector<string> nxt;
            for (const string &s: cur) {
                string nw = s + "00";
                nxt.push_back(nw);
            }
            int sz = (int(nxt.back().size()) - 3) / 2;
            string aux(sz, '0');
            nxt.push_back("1" + aux + "6" + aux + "9");
            nxt.push_back("9" + aux + "6" + aux + "1");
            cur = nxt;
        }
        for (const string &s: cur) cout << s << '\n';
    }
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

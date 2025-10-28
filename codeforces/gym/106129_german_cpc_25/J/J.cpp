#include <bits/stdc++.h>
using namespace std;

void solve() {
    string cmd; cin >> cmd;
    int n; cin >> n;
    string s; cin >> s;

    if (cmd == "Encode") {
        auto cnt = count_if(s.begin(), s.end(), [](char c) { return c == '0'; });
        
        if (cnt == 0 || cnt == n) {
            cout << s << endl;
            return;
        }

        int i = 0;
        while (s[i] == '1') i++;

        string r = string(i + 1, '2');
        cout << r << s.substr(i + 1) << endl;
    } else {
        assert(cmd == "Decode");
        auto cnt = count_if(s.begin(), s.end(), [](char c) { return c == '2'; });

        if (cnt == 0) {
            cout << s << endl;
            return;
        }

        while (cnt > 1) { cout << '1'; cnt--; }
        cout << '0';

        int idx = find(s.begin(), s.end(), '2') - s.begin();

        for (int i = (idx + 1) % n; i != idx;) {
            if (s[i] != '2') cout << s[i];
            i++;
            if (i == n) i = 0;
        }
        cout << endl;
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

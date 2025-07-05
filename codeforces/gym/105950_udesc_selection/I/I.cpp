#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<bool>> e(26, vector<bool>(26, 0));
    vector<int> in(26, 0);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < int(s.size()) - 1; j++) {
            int c1 = s[j] - 'a';
            int c2 = s[j + 1] - 'a';
            if (c1 == c2) continue;
            if (!e[c1][c2]) {
                e[c1][c2] = 1;
                in[c2]++;
            }
        }
    }
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    vector<int> ans;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        ans.push_back(node);
        for (int j = 0; j < 26; j++) {
            if (e[node][j]) {
                if (--in[j] == 0) {
                    q.push(j);
                }
            }
        }
    }
    if (ans.size() < 26) {
        cout << "NAO\n";
    }
    else {
        cout << "SIM\n";
        for (int a: ans) {
            cout << char(a + 'a');
        }
        cout << '\n';
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

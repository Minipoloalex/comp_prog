#include <bits/stdc++.h>
using namespace std;

int n;
int W;
string s;
int cur = 0;


void add(int idx) {
    cur++;
    if (s[idx] == 'W') W++;
}
void remove(int idx) {
    cur--;
    if (s[idx] == 'W') W--;
}

bool isgood(int sz) {
    int ans = 0;
    for (int i = 0; i < 2*n-1; i++) {
        for (int j = i + n; j <= 2*n-1; j++) {
            int cnt = (int)count(s.begin() + i, s.begin() + j, 'W');
            if (cnt == sz) ans++;
        }
    }
    return ans >= n;
}


void solve() {
    W = 0;
    int l = 0, r = 0;
    int mx = 0;
    cur = 0;
    while (r < 2*n-1) {
        add(r++);
        mx = max(mx, W);
        if (cur == n) {
            remove(l++);
        }
    }
    cout << mx << '\n';
    // assert(isgood(mx));
}

void test(int sz) {
    n = sz / 2;
    for (int i = 0; i < (1 << sz); i++) {
        s.clear();
        for (int j = 0; j < sz; j++) {
            if ((1 << j) & i) {
                s += "R";
            }
            else {
                s += "W";
            }
        }
        solve();
    }
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        cin >> n;
        cin >> s;
        solve();
    }
    // test(21);
    return 0;
}

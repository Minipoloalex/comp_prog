#include <bits/stdc++.h>
using namespace std;

bool check(int n, int want) {
    set<int> st({'a', 'e', 'i', 'o', 'u'});
    int cnt = 0, ys = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (char c: s) {
            c = (char)tolower(c);
            if (st.find(c) != st.end()) {
                cnt++;
            }
            if (c == 'y') {
                ys++;
            }
        }
    }
    return cnt <= want && cnt + ys >= want;
}

void solve() {
    int n1, n2, n3;
    cin >> n1 >> n2 >> n3;
    bool ans = check(n1, 5);
    ans &= check(n2, 7);
    ans &= check(n3, 5);
    cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

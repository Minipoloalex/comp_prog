#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    string s;
    cin >> s;
    char ch_cur = 0;
    int cur;

    int mx = 0;
    for (char ch: s) {
        if (ch != ch_cur)  {
            ch_cur = ch;
            cur = 0;
        }
        cur++;
        mx = max(cur, mx);
    }
    cout << mx << '\n';
    return 0;
}

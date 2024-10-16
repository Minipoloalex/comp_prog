#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    string s;
    cin >> s;
    int n = int(s.size());
    int mx_cnt = 0, curr_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            curr_cnt = 0;
        }
        else {
            assert(s[i] == '0');
            curr_cnt++;
            mx_cnt = max(mx_cnt, curr_cnt);
        }
    }
    cout << (mx_cnt + 1) / 2 << '\n';
    return 0;
}

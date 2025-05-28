#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int cnt0 = (int) count(s.begin(), s.end(), '0');
    int cnt1 = n - cnt0;
    string ans;
    int total = n / 2;
    int others = total - k;
    cnt0 -= others;
    cnt1 -= others;
    if (cnt0 < 0 || cnt1 < 0) {
        ans = "NO";
    }
    else {
        if (cnt0 % 2 == 0 && cnt1 % 2 == 0) {
            ans = "YES";
        }
        else ans = "NO";
    }
    cout << ans << '\n';
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

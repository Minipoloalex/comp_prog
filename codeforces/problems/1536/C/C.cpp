#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<pair<int,int>, int> mp;
    int d = 0, k = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'D') d++;
        else k++;
        int g = gcd(d, k);
        cout << ++mp[{d / g, k / g}] << " ";
    }
    cout << '\n';
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

#include <bits/stdc++.h>
using namespace std;

const int MAX = int(2e5);

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> act(MAX + 1);
    for (int i = 0; i < n; i++) {
        int s, d;
        cin >> s >> d;
        for (int j = s; j <= s + d; j++) {
            act[j] = 1;
        }
    }
    pair<int,int> mn = {INT_MAX, -1};
    for (int i = 0; i <= 480; i++) {
        int cnt = 0;
        for (int j = i; j <= MAX; j += x) {
            cnt += act[j];
        }
        if (cnt < mn.first) {
            mn = {cnt, i};
        }
    }
    cout << mn.second << " " << mn.first << '\n';
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

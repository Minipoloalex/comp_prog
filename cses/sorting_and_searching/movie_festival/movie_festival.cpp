#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

void solve() {
    int n;
    cin >> n;
    vector<ii> v(n);
    for (auto &x: v) {
        int a, b;
        cin >> a >> b;
        x = make_pair(b, a);
    }
    sort(v.begin(), v.end());
    int prev = 0, ans = 0;
    for (auto &[r, l]: v) {
        if (l >= prev) {
            prev = r;
            ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

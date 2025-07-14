#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    vector<int> missing(n, 1);
    for (int ai: a) {
        missing[ai-1] = 0;
    }
    queue<int> additional;
    for (int i = 0; i < n; i++) {
        if (missing[i]) {
            additional.push(i + 1);
        }
    }
    vector<int> found(n, 0);
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        int cur = a[i];
        if (found[a[i]-1]) {
            cur = additional.front();
            additional.pop();
        }
        found[a[i] - 1] = 1;
        ans[i] = cur;
    }
    for (int v: ans) cout << v << " ";
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

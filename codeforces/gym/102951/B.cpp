#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    sort(a.begin(), a.end());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > x) break;
        x -= a[i];
        ans++;
    }
    cout << ans << '\n';
    return 0;
}

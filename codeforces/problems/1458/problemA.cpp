#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<int64_t> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.rbegin(), a.rend());

    int64_t g = 0;
    for (int i = 0; i < n - 1; i++) {
        g = gcd(g, a[i] - a[i + 1]);
    }
    for (int j = 0; j < m; j++) {
        int64_t bj;
        cin >> bj;
        cout << gcd(g, a.back() + bj) << " ";
        // or gcd(a1 + bj, a1 - a2, a1 - a3, ..., a1 - an)
    }
    cout << '\n';
    return 0;
}

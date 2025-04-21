#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> v1, v2;
    if (n % 4 == 0) {
        for (int i = 1; i <= n / 2; i += 2) {
            v1.push_back(i);
            v1.push_back(n - i + 1);
            v2.push_back(i + 1);
            v2.push_back(n - (i + 1) + 1);
        }
    }
    else if ((n + 1) % 4 == 0) {
        v1.push_back(n / 2);
        v1.push_back((n + 1) / 2);
        v2.push_back(n);
        for (int i = 1; i < n / 2; i += 2) {
            v1.push_back(i);
            v1.push_back(n - i);
            v2.push_back(i + 1);
            v2.push_back(n - (i + 1));
        }
    }
    if (!v1.empty()) {
        cout << "YES\n";
        cout << v1.size() << '\n';
        for (int v: v1) cout << v << " ";
        cout << '\n';

        cout << v2.size() << '\n';
        for (int v: v2) cout << v << " ";
        cout << '\n';
    }
    else {
        cout << "NO\n";
    }
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

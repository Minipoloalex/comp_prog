#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    if (a == 1 && b == 1) {
        cout << "no\n";
    }
    else {
        if (a + b >= n + 2) {
            cout << "no\n";
            return;
        }
        bool rev = b == 1;
        if (b == 1) swap(a,b);
        vector<int> ans;
        cout << "yes\n";
        for (int i = 1; i < a; i++) {
            ans.push_back(i);
        }
        ans.push_back(n);
        for (int i = a; i < n - b + 1; i++) {
            ans.push_back(i);
        }
        for (int i = n - 1; i >= n - b + 1; i--) {
            ans.push_back(i);
        }
        if (rev) reverse(ans.begin(), ans.end());
        for (int val: ans) cout << val << " ";
        cout << '\n';
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

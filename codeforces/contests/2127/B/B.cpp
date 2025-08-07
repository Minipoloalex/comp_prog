#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    x--;
    string s;
    cin >> s;
    int rig = -1, lef = -1;
    for (int i = x + 1; i < n; i++) {
        if (s[i] == '#') {
            if (rig == -1) {
                rig = i;
            }
        }
    }
    for (int i = x - 1; i >= 0; i--) {
        if (s[i] == '#') {
            if (lef == -1) {
                lef = i;
            }
        }
    }
    int ans;
    if (lef == -1 && rig == -1) {
        ans = 1;
    }
    else if (lef == -1) {
        ans = min(x + 1, n - rig + 1);
    }
    else if (rig == -1) {
        ans = min(lef + 2, n - x);
    }
    else {
        int leftans = lef + 2;
        int rightans = n - rig + 1;
        ans = max(leftans, rightans);
        if (leftans < rightans) {
            ans = min(ans, x + 1);
        }
        else if (rightans < leftans) {
            ans = min(ans, n - x);
        }
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

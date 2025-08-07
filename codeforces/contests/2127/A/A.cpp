#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    bool ans = true;
    for (int i = 0; i < n - 2; i++) {
        set<int> nums;
        for (int j = i; j - i <= 2; j++) {
            if (a[j] != -1) {
                nums.insert(a[j]);
            }
        }
        if (nums.size() > 1 || (nums.size() == 1 && *nums.begin() == 0)) {
            ans = false;
            break;
        }
        if (nums.size() == 1) {
            for (int j = i; j - i <= 2; j++) {
                a[j] = *nums.begin();
            }
        }
    }
    cout << (ans ? "YES" : "NO") << '\n';
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

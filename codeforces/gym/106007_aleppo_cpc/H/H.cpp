#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;

    vector<int> ans;
    ans.push_back(a[0]);
    int i = 1;
    while (i < n) {
        if (i + 2 < n) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                ans.push_back(a[i]);
                ans.push_back(a[i + 1]);
                ans.push_back(a[i + 2]);
                i += 3;
            }
            else {
                ans.push_back(a[i]);
                i++;
            }
        }
        else if (i + 1 < n) {
            ans.push_back(a[i]);
            ans.push_back(a[i + 1]);
            i += 2;
        }
        else {
            ans.push_back(a[i]);
            i++;
        }
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

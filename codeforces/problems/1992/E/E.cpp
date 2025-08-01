#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s = to_string(n);
    int sz = int(s.size());
    string large = s + s + s + s + s + s;
    vector<pair<int,int>> ans;
    for (int a = 1; a <= int(1e4); a++) {
        int base_size = sz * a;
        for (int actual_size = 1; actual_size <= 6 && actual_size < base_size; actual_size++) {
            string cur = large.substr(0, actual_size);
            int b = base_size - actual_size;
            int value = n * a - b;
            if (to_string(value) == cur) {
                ans.emplace_back(a, b);
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto &[a, b]: ans) {
        cout << a << " " << b << '\n';
    }
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

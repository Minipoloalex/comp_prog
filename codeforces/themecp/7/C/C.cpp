#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (auto &xi: x) cin >> xi;
    vector<int> occ(n + 1, 0);
    for (auto &xi: x) occ[xi]++;
    int not_here = -1;
    for (int i = 1; i <= n; i++) {
        if (occ[i] == 0) not_here = i;
    }
    auto ask = [](int i, int j) {
        cout << "? " << i << " " << j << endl;
        int ans;
        cin >> ans;
        if (ans == -1) exit(1);
        return ans;
    };
    auto finish = [](char ans) {
        cout << "! " << ans << endl;
    };
    if (not_here != -1) {
        int other = 1;
        if (not_here == 1) other = 2;
        int d = ask(not_here, other);
        if (d == 0) {
            finish('A');
        }
        else finish('B');
    }
    else {
        int i = int(min_element(x.begin(), x.end()) - x.begin()) + 1;
        int j = int(max_element(x.begin(), x.end()) - x.begin()) + 1;
        int d1 = ask(i, j);
        int d2 = ask(j, i);
        if (d1 > n - 1 || (d1 == n - 1 && d1 == d2)) {
            finish('B');
        }
        else {
            finish('A');
        }
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

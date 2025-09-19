#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &ai: a) cin >> ai;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int L = accumulate(a.begin(), a.begin() + i + 1, 0) % 3;
            int mid = accumulate(a.begin() + i + 1, a.begin() + j + 1, 0) % 3;
            int R = accumulate(a.begin() + j + 1, a.end(), 0) % 3;
            if (L == R && R == mid) {
                cout << i + 1 << " " << j + 1 << '\n';
                return;
            }
            if (L != R && L != mid && mid != R) {
                cout << i + 1 << " " << j + 1 << '\n';
                return;
            }
        }
    }
    cout << "0 0\n";
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

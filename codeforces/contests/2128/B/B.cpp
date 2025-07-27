#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto &pi: p) cin >> pi;
    string s;
    int l = 0, r = n - 1;
    while (r - l + 1 >= 3) {
        int x = p[l];
        int z = p[l + 1];
        int y = p[r];
        if (y > x && z > x) {
            s += "RLL";
        }
        else if (y > x && z < x) {
            s += "LLR";
        }
        else if (y < x && z > x) {
            s += "LRL";
        }
        else if (y < x && z < x) {
            s += "RLL";
        }
        else {
            assert(0 == 1);
        }
        l += 2;
        r--;
    }
    for (int i = l; i <= r; i++) {
        s += 'L';
    }
    cout << s << '\n';
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

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int d;
    cin >> d;
    auto digits = [&](int nr) {
        int sm = 0;
        while (nr) {
            sm += nr % 10;
            nr /= 10;
        }
        return sm;
    };
    const int MAX = int(5e6);
    for (int i = 0; i < MAX; i++) {
        if (digits(i) == digits(i + d)) {
            cout << i << " " << i + d << '\n';
            return;
        }
    }
    cout << "NONE\n"; // debugging for N1
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

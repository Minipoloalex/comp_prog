#include <bits/stdc++.h>
using namespace std;

void solve() {
    int Ax = 0, Ay = 0;
    int Bx, By;
    cin >> Bx >> By;
    auto valid = [&](int Cx, int Cy) {
        int AB = abs(Ax - Bx) + abs(Ay - By);
        int AC = abs(Ax - Cx) + abs(Ay - Cy);
        int BC = abs(Bx - Cx) + abs(By - Cy);
        return AC * 2 == AB && BC * 2 == AB;
    };
    for (int x = 0; x <= 100; x++) {
        for (int y = 0; y <= 100; y++) {
            if (valid(x, y)) {
                cout << x << " " << y << '\n';
                return;
            }
        }
    }
    cout << "-1 -1\n";
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

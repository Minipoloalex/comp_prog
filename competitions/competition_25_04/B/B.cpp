#include <bits/stdc++.h>
using namespace std;

int solve() {
    int x1, y1, z1, x2, y2, z2;
    cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

    int res = 0;
    int aux = min(z1, y2);
    res += 2 * aux;
    z1 -= aux;
    y2 -= aux;

    aux = min(z1, z2);
    z1 -= aux;
    z2 -= aux;

    aux = min(y1, y2);
    y2 -= aux;
    y1 -= aux;

    aux = min(x1, z2);
    x1 -= aux;
    z2 -= aux;

    aux = min(x1, y2);
    x1 -= aux;
    y2 -= aux;

    aux = min(y1, x2);
    y1 -= aux;
    x2 -= aux;

    res -= 2 * y1;
    cout << res << '\n';
    return 0;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}

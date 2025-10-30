#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, rk, ck, rd, cd;
    cin >> n >> rk >> ck >> rd >> cd;
    int ans = 1;
    auto use = [&](int r, int c) {
        int manh = abs(rk - r) + abs(ck - c);
        int cheb = max(abs(rd - r), abs(cd - c));
        if (manh < cheb) {
            ans = max(ans, cheb);
            return cheb-manh;
        }
        return 0;
    };
    int d1 = use(rk, 0);
    use(min(n,rk+d1),0);
    use(max(0,rk-d1),0);

    int d2 = use(0, ck);
    use(0, min(n,ck+d2));
    use(0, max(0,ck-d2));

    int d3 = use(rk,n);
    use(min(n,ck+d3),n);
    use(max(0,ck-d3), n);

    int d4 = use(n,ck);
    use(n, min(n,ck+d4));
    use(n, max(0,ck-d4));
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

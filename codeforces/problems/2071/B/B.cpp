#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int64_t sm = int64_t(1 + n) * n / 2;
    int64_t aux = int64_t(sqrt(sm));

    if (aux * aux == sm) {
        cout << "-1\n";
    }
    else {
        int64_t s = 0;
        int i = 1;
        while (i <= n) {
            s += i;
            int64_t a = int64_t(sqrt(s));
            if (a * a == s) {   // if s perfect square
                cout << i + 1 << " " << i << " ";
                s += i + 1;
                i += 2;
            }
            else {
                cout << i << " ";
                i++;
            }
        }
        cout << '\n';
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

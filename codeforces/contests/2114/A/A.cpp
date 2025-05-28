#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int aux = int(sqrt(n));
    bool ans;
    if (aux * aux == n) {
        ans = true;
    }
    else {
        ans = false;
    }
    if (ans) {
        cout << "0 " << aux << '\n';
    }
    else {
        cout << "-1\n";
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

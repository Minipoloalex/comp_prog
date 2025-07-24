#include <bits/stdc++.h>
using namespace std;

void solve() {
    string a, b; cin >> a >> b;

    multiset<char> st_a(a.begin(), a.end()), st_b(b.begin(), b.end());

    if (st_a != st_b) {
        cout << "No\n";
        return;
    }

    string a_even, a_odd, b_even, b_odd;

    for (char c : a) {
        if ((c - 'a') % 2 == 0) a_even += c;
        else a_odd += c;
    }

    for (char c : b) {
        if ((c - 'a') % 2 == 0) b_even += c;
        else b_odd += c;
    }

    if (a_even == b_even && a_odd == b_odd) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

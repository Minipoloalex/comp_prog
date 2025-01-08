#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    multiset<int> curr;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        auto it = curr.upper_bound(k);
        if (it == curr.end()) { // noone bigger than this cube
            curr.insert(k);
        }
        else {
            // replace cube slightly bigger than me with myself
            curr.erase(it);
            curr.insert(k);
        }
    }
    cout << curr.size() << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    solve();
    return 0;
}

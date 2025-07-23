#include <bits/stdc++.h>
using namespace std;

const int MAX = int(1e6);

int fact[MAX + 1];

void precompute_facts() {   // count the number of 2's in the factorial
    fact[0] = 0;
    for (int i = 1; i <= MAX; i++) {
        int cnt = 0;
        int ii = i;
        while ((ii & 1) == 0) {
            cnt++;
            ii >>= 1;
        }
        fact[i] = fact[i - 1] + cnt;
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    n--;
    for (int i = 0; i <= n; i++) {
        int cnt = fact[n] - fact[n - i] - fact[i];  // is comb(n, i) even?
        if (cnt > 0) {
            cout << "0 ";
        }
        else {
            cout << k << " ";
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    precompute_facts();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

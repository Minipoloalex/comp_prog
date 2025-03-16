#include <bits/stdc++.h>
using namespace std;

const int MAX = int(1e6);
bitset<MAX + 1> bs;
vector<int> p;
void sieve() {
    bs.set();
    bs[0] = 0;
    bs[1] = 0;
    for (int i = 2; i <= MAX; i++) if (bs[i]) {
        for (int j = i; j <= MAX; j += i) {
            bs[j] = 0;
        }
        p.push_back(i);
    }
}

int factor(int x) {
    int ans = 1;
    for (int i = 0; i < int(p.size()) && p[i] * p[i] <= x; i++) {
        int cnt = 0;
        while (x % p[i] == 0) {
            x /= p[i];
            cnt++;
        }
        ans *= (cnt + 1);
    }
    if (x > 1) ans *= 2;
    return ans;
}

void solve() {
    int x;
    cin >> x;
    cout << factor(x) << '\n';
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    sieve();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int MAX_X =  int(2e5);

vector<int> divisors(int n) {
    vector<int> ans;
    for (int i = 1; 1LL * i * i <= n; i++) {
        if (n % i == 0) {
            ans.push_back(i);
            if (n / i != i) ans.push_back(n / i);
        }
    }
    return ans;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n), b(m);
    for (auto &ai: a) cin >> ai;
    for (auto &bi: b) cin >> bi;
    int64_t asum = accumulate(a.begin(), a.end(), 0LL);
    int64_t bsum = accumulate(b.begin(), b.end(), 0LL);

    vector<bool> canA(2*(MAX_X+1)), canB(2*(MAX_X+1));
    for (int i = 0; i < n; i++) {
        int64_t cur = asum - a[i];
        if (abs(cur) <= MAX_X) {
            canA[cur + MAX_X] = 1;
        }
    }
    for (int j = 0; j < m; j++) {
        int64_t cur = bsum - b[j];
        if (abs(cur) <= MAX_X) {
            canB[cur + MAX_X] = 1;
        }
    }

    while (q--) {
        int x;
        cin >> x;
        bool ans = false;
        auto check = [&](int divisor) {
            int fst = divisor + MAX_X;
            int snd = x / divisor + MAX_X;
            ans |= (canA[fst] && canB[snd]) || (canA[snd] && canB[fst]);
        };
        for (int divisor: divisors(abs(x))) {
            check(divisor);
            check(-divisor);
        }
        cout << (ans ? "YES" : "NO") << '\n';
    }
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

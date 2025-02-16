#include <bits/stdc++.h>
using namespace std;

int64_t pow_mod(int64_t a, int64_t b, int64_t m) {
    if (b == 0) return 1;
    if (b & 1) {
        return (a * pow_mod(a, b - 1, m)) % m;
    }
    else {
        int64_t aux = pow_mod(a, b / 2, m);
        return (aux * aux) % m;
    }
}

void solve()
{
    int64_t n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int64_t pm = (pow_mod(2, k, n) + n) % n;
    for (int i = 0; i < n; i++) {
        cout << s[(i * pm) % n];
    }
    cout << '\n';
}

int main()
{
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

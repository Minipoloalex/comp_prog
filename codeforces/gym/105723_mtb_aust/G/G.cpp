#include <bits/stdc++.h>
using namespace std;

int64_t powmod(int64_t a, int64_t b, int64_t p) {   // a^b % p
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * powmod(a, b - 1, p)) % p;
    int64_t aux = powmod(a, b / 2, p);
    return (aux * aux) % p;
}

const int MOD = 998244353;

vector<int> f(int n)
{
    vector<int> v;
    for(int i=2;i*1LL*i<=n;++i)
    {
        if(n%i==0)
        {
            int cnt = 0;
            while(n%i==0)
                n/=i, cnt++;
            v.push_back(cnt);
        }
    }
    if(n!=1)
        v.push_back(1);
    return v;
}

int64_t div_ans(int n, int x, int max_x) {
    int nrs = n - 1;
    int diff = max_x + 1;   // x + max_x - x + 1
    if (x == max_x || x == 0) {
        int64_t all = powmod(diff, nrs, MOD);
        int64_t without_one_side = powmod(diff - 1, nrs, MOD);
        return (all - without_one_side + MOD) % MOD;
    }
    else {
        // 2^x, 2^(x+max_x)
        int64_t all = powmod(diff, nrs, MOD);
        int64_t without_left, without_right;
        without_right = without_left = powmod(diff-1, nrs, MOD);
        int64_t without_both = powmod(diff-2, nrs, MOD);
        return (all - without_left - without_right + without_both + 2*MOD) % MOD;
    }
}

int64_t sum(int n, int cnt) {
    int64_t sm = 0;
    for (int i = 0; i <= cnt; i++) {
        sm = (sm + div_ans(n, i, cnt)) % MOD;
    }
    return sm;
}

void solve() {
    int a1, n;
    cin >> a1 >> n;
    vector<int> exp = f(a1);

    int64_t ans = 1;
    for (int p_exp: exp) {
        ans = ans * sum(n, p_exp) % MOD;
    }
    cout << ans << '\n';
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

#include <bits/stdc++.h>
using namespace std;

const int MAX_P = int(1e6);

bitset<MAX_P> bs;

void sieve() {
    bs.set();
    bs[0] = bs[1] = 0;
    for (int64_t i = 2; i < MAX_P; i++) if (bs[i]) {    // i is a prime
        for (int64_t j = i * i; j < MAX_P; j += i) bs[j] = 0;
    }
}

string solve(int64_t ai) {
    // to have 3 divisors, a number must be the square of a prime
    int64_t p = int64_t(sqrtl(ai));
    if (bs[p] && p * p == ai) return "YES";
    return "NO";
}

int main() {
    cin.tie(0)->ios::sync_with_stdio(0);
    sieve();
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int64_t ai;
        cin >> ai;
        cout << solve(ai) << '\n';
    }
    return 0;
}

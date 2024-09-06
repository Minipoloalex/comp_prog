#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

ull level_n(ull n) {
    // sum ap a0 = 0
    ull first_sum_ap = (n * n - n)/2;
    ull second_sum_ap = (n + 1) * (n);
    return first_sum_ap + second_sum_ap;
}

int main() {
    ull n; cin >> n;
    ull lb = 0;
    ull ub = n;
    ull res = 0;
    while (lb <= ub) {
        ull middle = (lb + ub)/2;
        // cout << middle << ": " << level_n(middle) << endl;
        if (level_n(middle) < n) {
            res = middle;
            lb = middle + 1;
        }
        else if (level_n(middle) > n) {
            // would need more cards
            ub = middle - 1;
        }
        else {
            res = middle;
            break;
        }
    }
    cout << res << endl;
    return 0;
}
